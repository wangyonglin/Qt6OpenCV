QT       += core gui multimedia opengl widgets
QT += gui core gui multimedia opengl widgets openglwidgets
TEMPLATE = lib
DEFINES += LIBQT6OPENCV_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/include/opencv4
CONFIG += debug_and_release
linux-g++* {
    message(Compling with linux-g++)
    CONFIG(debug, debug|release){
        message(Debug build)
        TARGET = Qt6OpenCV

        release

    }

    CONFIG(release, debug|release){
        message(Release build)
        TARGET = Qt6OpenCV

    }

    #DEFINES += CSM_TARGET_LINUX_GL
}
SOURCES += \
    QCameraPlayer.cpp \
    QCameraReader.cpp \
    QCameraThreader.cpp

HEADERS += \
    QCameraPlayer.h \
    QCameraReader.h \
    QCameraThreader.h \
    libQt6OpenCV_global.h


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
