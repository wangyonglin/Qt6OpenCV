#ifndef QWANGOPENCV_H
#define QWANGOPENCV_H

#include "QtWangOpenCV_global.h"

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
#include <QGLShaderProgram>
#include <mutex>

#include "QWangCameraThreader.h"

class  QWangCameraPlayer : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QWangCameraPlayer(QWidget *parent = nullptr);
    void play(QString name, int framerate);
    void stop();
private slots:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void onRefreshFrame(const QImage &image);
private:
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QOpenGLShaderProgram *program;
    QOpenGLTexture *texture;
    QMatrix4x4 projection;
    QImage dstQImage;
    QWangCameraThreader *qWangCameraThreader;
signals:
    void finished();
    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

};

#endif // QWANGOPENCV_H
