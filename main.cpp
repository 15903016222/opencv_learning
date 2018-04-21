#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("<0>原始图像");
    // 读取原始图像，并显示
    Mat srcImage = imread("../dilate.jpg");
    imshow("<0>原始图像", srcImage);

    /* ------------膨胀操作dilate()------------- */
    namedWindow("<1>膨胀操作【效果图】");
    Mat dilateImage;
    Mat element;
    // 获取自定义核
    // 描述：获取自定义核的信息
    // 第一个参数： 自定义核的形状
    // 第二个参数： 自定义核的大小
    // 第三个参数： 锚点位置
    element = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
    // 膨胀操作
    // 描述：对图像进行膨胀操作
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 自定义核
    // 第四个参数： 锚点 默认值Point(-1, -1)
    // 第五个参数： 迭代使用dilate()函数的次数，默认值1
    // 第六个参数： 用于推断图像外部像素的某种边界模式，默认值：BORDER_CONSTANT
    // 第七个参数： 一般不用特别关注，如果用到，需要到文档中仔细阅读
    dilate(srcImage,
           dilateImage,
           element,
           Point(-1, -1),
           1,
           BORDER_CONSTANT,
           morphologyDefaultBorderValue());
    // 显示效果图
    imshow("<1>膨胀操作【效果图】", dilateImage);

    /* -------------腐蚀操作erode()------------- */
    namedWindow("<2>腐蚀操作【原图】");
    // 读取原始图像
    Mat srcErodeImage = imread("../erode.jpg");
    imshow("<2>腐蚀操作【原图】", srcErodeImage);

    // 腐蚀操作
    namedWindow("<3>腐蚀操作【效果图】");
    Mat dstErodeImage;
    // 腐蚀操作
    // 描述：对图像进行腐蚀操作
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 自定义核
    // 第四个参数： 锚点 默认值Point(-1, -1)
    // 第五个参数： 迭代使用dilate()函数的次数，默认值1
    // 第六个参数： 用于推断图像外部像素的某种边界模式，默认值：BORDER_CONSTANT
    // 第七个参数： 一般不用特别关注，如果用到，需要到文档中仔细阅读
    erode(srcErodeImage,
          dstErodeImage,
          element,
          Point(-1, -1),
          1,
          BORDER_CONSTANT,
          morphologyDefaultBorderValue());
    imshow("<3>腐蚀操作【效果图】", dstErodeImage);

    waitKey(0);
    return 0;
}
