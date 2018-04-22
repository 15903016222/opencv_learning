#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    // 创建窗口 读取图片 显示原图
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../resize.jpg");
    imshow("<0>【原图】", srcImage);

    // 创建窗口 图像调整后的矩阵 图像调整尺寸 显示效果图
    namedWindow("<1>【效果图】");
    namedWindow("<2>【效果图】");
    Mat dstImage1, dstImage2;

    // 向上取样 并模糊一张图像 也就是放大一张图像
    // 描述： 向上取样，一般用于放大图像
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像大小
    // 第四个参数： 一般使用默认值，不用太关心
    pyrUp(srcImage,
          dstImage1,
          Size(srcImage.cols << 1, srcImage.rows << 1),
          BORDER_DEFAULT);
    imshow ("<1>【效果图】", dstImage1);

    // 向下取样 并模糊一张图像
    // 描述：向下取样，并模糊一张图片，也就是缩小一张图像
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像大小
    // 第四个参数： 使用默认值，一般不关心
    pyrDown(srcImage,
            dstImage2,
            Size(srcImage.cols >> 1, srcImage.rows >> 1),
            BORDER_DEFAULT);
    imshow("<2>【效果图】", dstImage2);

    waitKey(0);
    return 0;
}
