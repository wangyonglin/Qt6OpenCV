#include "CameraPlayer.h"
#include <QCameraInfo>
#include <QBitmap>
#include "OpenGLPlayer.h"
CameraPlayer::CameraPlayer(QWidget *parent)
    :QWangOpenGL(parent),
      cameraThread(new CameraThreader(this))
{
    //    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    //    qDebug() << "Found" << cameras.count() << "cameras:";

    //    for (const QCameraInfo &cameraInfo : cameras) {
    //        qDebug() << "Camera:" << cameraInfo.deviceName();
    //        qDebug() << "Description:" << cameraInfo.description();
    //        qDebug() << "Position:" << cameraInfo.position();
    //        qDebug() << "Orientation:" << cameraInfo.orientation();
    //    }

    connect(cameraThread,&CameraThreader::onRefreshFrame,this,&QWangOpenGL::onRefreshFrame);
}

bool CameraPlayer::play(QString name,int framerate)
{
    return cameraThread->play(name,width(),height(),framerate);
}


void CameraPlayer::stop()
{
    cameraThread->stop();
}



/*
{
    QString pipeline =QString("gst-launch-1.0 v4l2src device=%1 ! videoconvert ! videoscale ! 'video/x-raw, width=%2, height=%3 ,framerate=%4/1' ! autovideosink")
            .arg(name).arg(width).arg(height).arg(framerate);
    qDebug() << "pipeline:" << pipeline;
    capture= make_unique<VideoCapture>(pipeline.toStdString(),CAP_GSTREAMER);

    if (!capture->isOpened()) {
        qFatal("无法打开摄像头");
        return false;
    }
    qDebug() << "open camera sucress";
    //capture->set(CAP_PROP_FPS, framerate);

    connect(timer, &QTimer::timeout, [&]() {
        Mat frame;
        if(!capture->read(frame)) return;
        //  *capture >> frame; // 从摄像头读取新的帧
        if(!frame.empty()){
            if(bMatteing){
                Mat hsvframe, mask;
                Scalar  lowerb=  Scalar(35, 43, 46);
                Scalar  upperb=  Scalar(155, 255, 255);
                hsvframe=InRangeHSV(frame,mask,lowerb,upperb);
                Mat matframe= Matting(frame,mask);
                QImage image= MattoImage(matframe);
                image.scaled(size(), Qt::IgnoreAspectRatio);
                bufferImage=QPixmap::fromImage(image);
                update();
            }else{
                QImage image= MattoImage(frame);
                bufferImage=QPixmap::fromImage(image);
                update();
            }

        }
    });
    timer->start(framepts); // 每秒30帧

}
*/
