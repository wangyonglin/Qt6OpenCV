#include <QApplication>

#include <Qt6OpenCV/QCameraPlayer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt6OpenCV::QCameraPlayer player;
    player.resize(800,600);
    player.play();
    player.show();
    player.stop();
    return a.exec();
}

