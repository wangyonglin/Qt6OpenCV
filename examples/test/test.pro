QT       += core gui opengl widgets
# In Qt6 to use QOpenglWidget, we need add QT += openglwidgets.
greaterThan(QT_MAJOR_VERSION, 5){
    message(Building with Qt6 or Higher)
    QT += openglwidgets multimediawidgets multimedia
}

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/include/opencv4

INCLUDEPATH += $$PWD/../../libQt6OpenCV/include

CONFIG += debug_and_release
linux-g++* {
    message(Compling with linux-g++)
    CONFIG(debug, debug|release){
        message(Debug build)
        LIBS += -L$$PWD/../../build/Desktop_Qt_6_7_2-Debug/libQt6OpenCV -lQt6OpenCV \
        -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio
        LIBS += -Wall -lpthread  -lgomp   -ldl
        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        LIBS += -L$$PWD/../../build/Desktop_Qt_6_7_2-Debug/libQt6OpenCV -lQt6OpenCV

    }

    DEFINES += CSM_TARGET_LINUX_GL
}


SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
