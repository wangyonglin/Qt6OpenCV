QT       += core gui multimedia opengl multimediawidgets \
    widgets

TEMPLATE = lib
DEFINES += QTWANGOPENCV_LIBRARY

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

SOURCES += \
    QWangCameraPlayer.cpp \
    QWangCameraThreader.cpp

HEADERS += \
    QWangCameraPlayer.h \
    QWangCameraThreader.h \
    QtWangOpenCV_global.h

# Default rules for deployment.
unix {
        INCLUDEPATH +=/home/wangyonglin/github/QtWangBase
        LIBS +=  -L/home/wangyonglin/github/build-QtWangBase-Rk3588_Buildroot_aarch64-Debug \
        -lQtWangBase
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
