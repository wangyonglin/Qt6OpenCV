#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
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
#include <QWangThread.h>

using namespace cv;
using namespace std;

class QWangCameraThreader : public QtWangThread
{
    Q_OBJECT
public:
    explicit QWangCameraThreader(QObject *parent = nullptr);
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
signals:
    // QWangThread interface
    void onRefreshFrame(const QImage & image);
protected:
    virtual void loopRunnable() override;
};

#endif // CAMERATHREAD_H
