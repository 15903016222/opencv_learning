#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

int main(int argc, char *argv[])
{
    VideoCapture capture(0);
    Mat edges;

    while (1)
    {
        Mat frame;
        capture >> frame;
        if (frame.empty()) {
            break;
        }

        cvtColor(frame, edges, CV_RGB2GRAY);

        blur(edges, edges, Size(3, 3));

        Canny(edges, edges, 0, 30, 3);

        imshow("摄像头", edges);
        if (waitKey(20) == 27)//27是键盘摁下esc时，计算机接收到的ascii码值
        {
            break;
        }
    }

    return 0;
}
