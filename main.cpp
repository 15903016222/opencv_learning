#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> // highgui模块头文件
#include <opencv2/imgproc/imgproc.hpp> // 图像处理函数头文件

using namespace cv;

int main(int argc, char *argv[])
{
    Mat srcImage = imread("../blur.jpg"); // 载入图像
    imshow("原始图", srcImage); // 显示图像

    // 均值滤波操作
    Mat dstImage;
    blur(srcImage, dstImage, Size (7, 7)); // 腐蚀操作函数
    imshow("效果图---均值滤波", dstImage);

    waitKey(0); // 等待按键按下

    return 0;
}

