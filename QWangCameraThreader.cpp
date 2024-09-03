#include "QWangCameraThreader.h"
#include <QDateTime>

QWangCameraThreader::QWangCameraThreader(QObject *parent)
    : QtWangThread(parent)
{

}

void QWangCameraThreader::setCameraWidth(int width)
{
    camera_width=width;
}

void QWangCameraThreader::setCameraHeight(int height)
{
     camera_height=height;

}

void QWangCameraThreader::setCameraFramerate(int framerate)
{
     camera_framerate=framerate;
}

bool QWangCameraThreader::open(QString name)
{
//    QString pipeline =QString("gst-launch-1.0 v4l2src device=%1 ! videoconvert ! videoscale ! 'video/x-raw,width=%2,height=%3,framerate=%4/1' ! autovideosink")
//            .arg(name).arg(width).arg(height).arg(framerate);

//    qDebug() << "pipeline:" <<pipeline;
    capture= make_unique<VideoCapture>(name.toStdString(),CAP_V4L2);

    if (!capture->isOpened()) {
        qFatal("无法打开摄像头");
        return false;
    }
    capture->set(CAP_PROP_FRAME_WIDTH,camera_width);
    capture->set(CAP_PROP_FRAME_HEIGHT,camera_height);
    capture->set(CAP_PROP_FPS,camera_framerate);

    //    #关闭白平衡，解决偏色问题
    capture->set(CAP_PROP_AUTO_WB,0);
    //    #设置曝光为手动模式
    capture->set(CAP_PROP_AUTO_EXPOSURE,1);
    //    #设置曝光的值为0
    capture->set(CAP_PROP_EXPOSURE,100);
   loopStart();
    return true;
}

void QWangCameraThreader::close()
{
    loopStop();
    if(capture)
    {
        capture->release();
    }

}
void QWangCameraThreader::loopRunnable()
{
    //            Mat hsvframe, mask;
    //            Scalar  lowerb=  Scalar(35, 43, 46);
    //            Scalar  upperb=  Scalar(155, 255, 255);
    //            hsvframe=InRangeHSV(frame,mask,lowerb,upperb);
    //            Mat matframe= Matting(frame,mask);
    //  frame.convertTo(dstframe, CV_8U, 255.0 / 65535.0, 0);

    if(capture->isOpened())
    {

        Mat dstMat;
        if(capture->read(dstMat))
        {

            // 获取当前日期和时间
            //QDateTime currentDateTime = QDateTime::currentDateTime();
            //QString filename=  currentDateTime.toString("yyyyMMddhhmmss.png");
            //imwrite(filename.toStdString(),rgbFrame);
            QImage dstQImage= cvMatToQImage(dstMat);
            emit onRefreshFrame(dstQImage);
        }else{
           loopStop();
        }


    }
}




QPixmap QWangCameraThreader::scaled2QImage(const QImage & image)
{
    QImage scaledImage =image.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(scaledImage);
}

Mat QWangCameraThreader::InRangeHSV(const Mat &frame,Mat &mask,Scalar & lowerb,Scalar & upperb)
{
    Mat hsv;
    //将每一帧的图像转换到hsv空间
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    //绿幕的颜色范围，将结果存在mask中
    // inRange(hsv, lowerb,upperb, mask);
    inRange(hsv, lowerb, upperb, mask);
    //对mask进行形态学操作
    //定义一个结构
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    //对mask进行形态学闭操作
    morphologyEx(mask, mask, MORPH_CLOSE, k);
    erode(mask, mask, k);
    //高斯模糊
    GaussianBlur(mask, mask, Size(3, 3), 0, 0);
    return mask;
}

Mat QWangCameraThreader::Matting(Mat frame, Mat mask)
{
    Mat dst = Mat::zeros(frame.size(), CV_8UC4);
    int dims =  dst.channels();
    //qDebug() << "######" << dims << "######";
    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

            if (p == 0)
            {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
                dst.at<Vec4b>(i, j)[0] = frame.at<Vec3b>(i, j)[0];
                dst.at<Vec4b>(i, j)[1] = frame.at<Vec3b>(i, j)[1];
                dst.at<Vec4b>(i, j)[2] = frame.at<Vec3b>(i, j)[2];
                dst.at<Vec4b>(i, j)[3] = 255;
            } else if(p == 255){
                dst.at<Vec4b>(i, j) =  Vec4b(0, 0, 0,0);
            }
        }
    }

    return dst;
}

Mat QWangCameraThreader::Replace(Mat frame, Mat mask, Mat bg)
{
    Mat dst = Mat::zeros(frame.size(), frame.type());

    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            int p = mask.at<uchar>(i, j);  //传入的mask是张二值图,p为当前mask像素值

            if (p == 0)
            {   //代表mask此时为前景，将绿幕视频中的前景像素赋给dst
                dst.at<Vec3b>(i, j) = frame.at<Vec3b>(i, j);
            }
            else if (p == 255)
            {
                //代表mask此时为背景，将背景图像素赋给dst
                dst.at<Vec3b>(i, j) = bg.at<Vec3b>(i,j);
            }

        }
    }

    return dst;
}







void QWangCameraThreader::yuyvToRgb(unsigned char *yuv_buffer,unsigned char *rgb_buffer,int iWidth,int iHeight)
{
    int x;
    int z=0;
    unsigned char *ptr = rgb_buffer;
    unsigned char *yuyv= yuv_buffer;
    for (x = 0; x < iWidth*iHeight; x++)
    {
        int r, g, b;
        int y, u, v;

        if (!z)
            y = yuyv[0] << 8;
        else
            y = yuyv[2] << 8;
        u = yuyv[1] - 128;
        v = yuyv[3] - 128;

        r = (y + (359 * v)) >> 8;
        g = (y - (88 * u) - (183 * v)) >> 8;
        b = (y + (454 * u)) >> 8;
        *(ptr++) = (r > 255) ? 255 : ((r < 0) ? 0 : r);
        *(ptr++) = (g > 255) ? 255 : ((g < 0) ? 0 : g);
        *(ptr++) = (b > 255) ? 255 : ((b < 0) ? 0 : b);

        if(z++)
        {
            z = 0;
            yuyv += 4;
        }
    }
}
/*
 * 初始化代码默认设置输出的图像格式是YUYV，在windows和Linux系统上是支持的，这个可能与摄像头有关，实际需要测试调整；Android系统上只支持NV21格式,如果是Android系统上运行，要记得修改格式
 */
void QWangCameraThreader::nv21ToRgb24(unsigned char *yuyv, unsigned char *rgb, int width, int height)
{
    const int nv_start = width * height ;
    int rgb_index = 0; //index = 0,
    uint8_t y, u, v;
    int r, g, b, nv_index = 0,i, j;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j ++){
            //nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
            nv_index = i / 2  * width + j - j % 2;

            y = yuyv[rgb_index];
            u = yuyv[nv_start + nv_index ];
            v = yuyv[nv_start + nv_index + 1];

            r = y + (140 * (v-128))/100;  //r
            g = y - (34 * (u-128))/100 - (71 * (v-128))/100; //g
            b = y + (177 * (u-128))/100; //b

            if(r > 255)   r = 255;
            if(g > 255)   g = 255;
            if(b > 255)   b = 255;
            if(r < 0)     r = 0;
            if(g < 0)     g = 0;
            if(b < 0)     b = 0;

            //index = rgb_index % width + (height - i - 1) * width;
            //rgb[index * 3+0] = b;
            //rgb[index * 3+1] = g;
            //rgb[index * 3+2] = r;

            //颠倒图像
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 1] = b;
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 2] = g;
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 3] = r;

            //正面图像
            rgb[i * width * 3 + 3 * j + 0] = b;
            rgb[i * width * 3 + 3 * j + 1] = g;
            rgb[i * width * 3 + 3 * j + 2] = r;

            rgb_index++;
        }
    }
}

QImage QWangCameraThreader::cvMatToQImage(const cv::Mat &inMat) {
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(static_cast<uchar *>(inMat.data), inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
        return image;
    }
        // 8-bit, 3 channel
    case CV_8UC3: {
        Mat dstMat;
        cvtColor(inMat,dstMat, COLOR_BGR2RGB);
        QImage image(static_cast<uchar *>(dstMat.data), dstMat.cols, dstMat.rows, static_cast<int>(dstMat.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    }
        // 8-bit, 1 channel
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;
        // only create our color table once
        if (sColorTable.isEmpty()) {
            for (int i = 0; i < 256; ++i) {
                sColorTable.push_back(qRgb(i, i, i));
            }
        }
        QImage image(static_cast<uchar *>(inMat.data), inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
        return image;
    }
    default:
        break;
    }

    return QImage();
}
