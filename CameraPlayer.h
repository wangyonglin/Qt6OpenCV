#ifndef CAMERAPLAYER_H
#define CAMERAPLAYER_H
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QBitmap>
#include "CameraThreader.h"
#include "QWangOpenGL.h"

using namespace cv;
using namespace std;

class CameraPlayer : public QWangOpenGL
{
    Q_OBJECT
public:
    explicit CameraPlayer(QWidget *parent = nullptr);
    void stop();
    bool play(QString name, int framerate);
private:
        CameraThreader *cameraThread;
        QBitmap qBitmap;
        QImage  paintQimage;
        Scalar  lowerb;
        Scalar  upperb;
        bool bMatteing =false;

};

#endif // CAMERAPLAYER_H
