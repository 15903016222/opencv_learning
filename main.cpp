#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("<0>原始图像【原图】");
    namedWindow("<1>中值滤波操作【效果图】");

    // 读取图像并显示
    Mat srcImage = imread("../medianblur.jpg", 1);
    imshow("<0>原始图像【原图】", srcImage);

    /* ---------中值滤波操作函数[medianBlur()]-------- */
    // 中值滤波操作
    Mat dstMediaImage;
    // 第一个参数： 原始图像，输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 孔径线性尺寸,这个参数必须是大于1的奇数，如：3， 5， 7， 9 ... ...
    medianBlur(srcImage, dstMediaImage, 3);

    // 显示效果图像
    imshow("<1>中值滤波操作【效果图】", dstMediaImage);


    waitKey(0);
    return 0;
}
