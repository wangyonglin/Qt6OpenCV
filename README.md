# Qt6OpenCV 库

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
