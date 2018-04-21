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

    /* ------------双边滤波操作[bilateralFilter()]-------------- */
    namedWindow("<2>双边滤波操作效果图");
    Mat dstBilateralImage;
    // 第一个参数： 输入原始图像
    // 第二个参数： 输出图像
    // 第三个参数： 表示滤波过程中，每个像素的邻域，如果设置为非正数，则由第五个参数计算出来
    // 第四个参数： 颜色空间域的sigma值，这个值越大，说明该像素邻域内有越宽广的颜色混合进来
    // 第五个参数： 这个值越大，意味着越远的像素会相互影响
    // 第六个参数： 一般不考虑，不需要太关心
    bilateralFilter(srcImage,
                    dstBilateralImage,
                    25,
                    25 * 2,
                    25 / 2/*, BORDER_DEFAULT*/);

    // 显示双边滤波操作的效果图
    imshow("<2>双边滤波操作效果图", dstBilateralImage);

    waitKey(0);
    return 0;
}
