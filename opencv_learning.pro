TARGET = opencv_learning

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /home/ws/tmp/opencv-master/build/lib/libopencv_world.so
