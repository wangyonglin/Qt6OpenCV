#ifndef QCAMERAPLAYER_H
#define QCAMERAPLAYER_H

#include <QWidget>
#include "libQt6OpenCV_global.h"
#include "QCameraReader.h"
#include <QCameraDevice>
#include <QMediaDevices>

#include <QWidget>
#include <QObject>
#include <QString>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>



namespace Qt6OpenCV {
class LIBQT6OPENCV_EXPORT QCameraPlayer : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QCameraPlayer(QWidget *parent = nullptr);
    ~QCameraPlayer();
    void play(const QString & device="/dev/video1");
    void stop();
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();

private:
    QCameraReader * reader=nullptr;
    //shader程序
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer vbo;

    int idY,idU,idV;

    int width,height;

    //FFmpegDecoder *decoder;

    uchar* ptr;
signals:
    void finished();
};

}


#endif // QCAMERAPLAYER_H
