#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> // highgui模块头文件
#include <opencv2/imgproc/imgproc.hpp> // 图像处理函数头文件

using namespace cv;

int main(int argc, char *argv[])
{
    Mat srcImage = imread("../erode.jpg"); // 载入图像
    imshow("原始图", srcImage); // 显示图像
    // 进行腐蚀操作
    Mat element = getStructuringElement(MORPH_RECT, Size (5, 5));
    Mat dstImage;
    erode(srcImage,dstImage, element); // 腐蚀操作函数
    imshow("效果图---腐蚀操作", dstImage);

    waitKey(0); // 等待按键按下

    return 0;
}

