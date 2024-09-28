#ifndef QCAMERAREADER_H
#define QCAMERAREADER_H
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


#include <QObject>
#include "QCameraThreader.h"

using namespace cv;
using namespace std;
namespace Qt6OpenCV {
class QCameraReader : public QCameraThreader
{
    Q_OBJECT
public:
    explicit QCameraReader(QObject *parent = nullptr);
    ~QCameraReader();
    void setCameraWidth(int width);
    void setCameraHeight(int height);
    void setCameraFramerate(int framerate);

    bool open(QString name);
    void close();
    QImage cvMatToQImage(const cv::Mat &inMat);

private:

    int camera_width=800;
    int camera_height=600;
    int camera_framerate=30;
    unique_ptr<VideoCapture> capture;
    QPixmap scaled2QImage(const QImage &image);
    Mat InRangeHSV(const Mat &frame, Mat &mask, Scalar &lowerb, Scalar &upperb);
    Mat Matting(Mat frame, Mat mask);
    Mat Replace(Mat frame, Mat mask, Mat bg);
    void yuyvToRgb(unsigned char *yuv_buffer, unsigned char *rgb_buffer, int iWidth, int iHeight);
    void nv21ToRgb24(unsigned char *yuyv, unsigned char *rgb, int width, int height);
    unique_ptr<unsigned char[]> yuv420_data;
    int yuv420_size =0;
signals:
    // QWangThread interface
    void sigFirst(uchar* p,int w,int h);
    void refresh();
protected:
    virtual void loop() override;
};
}


#endif // QCAMERAREADER_H
