#ifndef QCAMERATHREADER_H
#define QCAMERATHREADER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "libQt6OpenCV_global.h"

namespace Qt6OpenCV {
class LIBQT6OPENCV_EXPORT QCameraThreader : public QThread
{

public:
    explicit QCameraThreader(QObject *parent = nullptr);
    ~QCameraThreader() override;

    enum State
    {

        Stoped,     ///<停止状态，包括从未启动过和启动后被停止
        Running,    ///<运行状态
        Paused      ///<暂停状态
    };

    State state() const;


public slots:
    void start(Priority pri = InheritPriority);
    void stop();
    void pause();
    void resume();
protected:
    virtual void run() override final;
    virtual void loop()=0;
private:
    std::atomic_bool pauseFlag;
    volatile std::atomic_bool stopFlag;
    QMutex mutex;
    QWaitCondition condition;
};
}


#endif // QCAMERATHREADER_H
