#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;

int main(int argc, char *argv[])
{
    VideoCapture capture(0);

    Mat frame;

    while (1)
    {
        capture >> frame;
        if (frame.empty()) {
            break;
        }
        imshow("摄像头", frame);
        if (waitKey(20) == 27)//27是键盘摁下esc时，计算机接收到的ascii码值
        {
            break;
        }
    }

    return 0;
}
