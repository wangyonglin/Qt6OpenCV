# QtWangCamera 库
INCLUDEPATH +=/home/wangyonglin/github/QtWangBase
LIBS +=  -L/home/wangyonglin/github/build-QtWangBase-Rk3588_Buildroot_aarch64-Debug \
-lQtWangBase

INCLUDEPATH +=/home/wangyonglin/github/QtWangCamera
LIBS +=  -L/home/wangyonglin/github/build-QtWangCamera-Rk3588_Buildroot_aarch64-Debug \
-lQtWangCamera

#            INCLUDEPATH +=/home/wangyonglin/github/FFmpegPlayer
#            LIBS += -L/home/wangyonglin/github/build-FFmpegPlayer-Rk3588_Buildroot_aarch64-Debug \
#                 -lFFmpegPlayer

    INCLUDEPATH +=/usr/aarch64-linux-gnu/include
    LIBS += -L/usr/aarch64-linux-gnu/lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavutil \
            -lswscale \
            -lswresample \
            -lopencv_core \
            -lopencv_highgui \
            -lopencv_imgcodecs \
            -lopencv_imgproc \
            -lopencv_videoio
    LIBS += -Wall -lpthread  -lgomp   -ldl
