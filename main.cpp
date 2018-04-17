#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat srcImage = imread("../1.jpg"); // 载入图像
    imshow("原始图", srcImage); // 显示图像
    waitKey(0); // 等待按键按下

    return 0;
}

