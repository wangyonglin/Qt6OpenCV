#include "QCameraThreader.h"


Qt6OpenCV::QCameraThreader::QCameraThreader(QObject *parent)
    : QThread(parent),
    pauseFlag(false),
    stopFlag(false)
{

}

Qt6OpenCV::QCameraThreader::~QCameraThreader()
{

}


Qt6OpenCV::QCameraThreader::State Qt6OpenCV::QCameraThreader::state() const
{
    State s = Stoped;
    if (!isRunning())
    {
        s = Stoped;
    }
    else if (isRunning() && pauseFlag)
    {
        s = Paused;
    }
    else if (isRunning() && (!pauseFlag))
    {
        s = Running;
    }
    return s;
}

void Qt6OpenCV::QCameraThreader::start(Priority pri)
{
    QThread::start(pri);
}



void Qt6OpenCV::QCameraThreader::stop()
{
    if (isRunning())
    {
        stopFlag = true;
        condition.wakeAll();
        quit();
        wait();
    }
}

void Qt6OpenCV::QCameraThreader::pause()
{
    if (isRunning())
    {
        pauseFlag = true;
    }
}

void Qt6OpenCV::QCameraThreader::resume()
{
    if (isRunning())
    {
        pauseFlag = false;
        condition.wakeAll();
    }
}

void Qt6OpenCV::QCameraThreader::run()
{
    //qDebug() << "enter QYonglinThreader : " << QYonglinThreader::currentQYonglinThreaderId();
    while (!stopFlag)
    {

        loop(); // do something...

        if (pauseFlag)
        {
            mutex.lock();
            condition.wait(&mutex);
            mutex.unlock();
        }
    }
    pauseFlag = false;
    stopFlag = false;

    //qDebug() << "exit QYonglinThreader : " << QYonglinThreader::currentQYonglinThreaderId();
}


