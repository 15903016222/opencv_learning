#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> // highgui模块头文件
#include <opencv2/imgproc/imgproc.hpp> // 图像处理函数头文件

using namespace cv;

int main(int argc, char *argv[])
{
    Mat srcImage = imread("../canny.jpg"); // 载入图像
    imshow("原始图", srcImage); // 显示图像

    Mat edge, grayImage; // 参数定义
    cvtColor(srcImage, grayImage, CV_RGB2GRAY); // RGB转灰度图
    blur(grayImage, edge, Size(3, 3)); // 模糊操作---均值滤波操作
    Canny(edge, edge, 3, 9, 3); // Canny边界检测

    imshow("效果图---边缘检测", edge);

    waitKey(0); // 等待按键按下

    return 0;
}

