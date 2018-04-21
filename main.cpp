#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建原图窗口，读取图像，显示图像
    namedWindow("<0>【原图】");
    Mat srcImage = imread("../open.jpg");
    imshow ("<0>【原图】", srcImage);

    // 创建效果图像， 获取自定义内核， 形态学操作， 显示效果图
    Mat dstImage;
    namedWindow("<1>形态学操作【效果图】");
    // 定义自定义内核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    // 描述：利用膨胀和腐蚀操作，进行高级的形态学变换
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 形态学运算的类型
    //            MORPH_OPEN----------开运算
    //            MORPH_CLOSE---------闭运算
    //            MORPH_GRADIENT------形态学梯度
    //            MORPH_TOPHAT--------顶帽
    //            MORPH_BLACKHAT------黑帽
    //            MORPH_ERODE---------腐蚀操作
    //            MORPH_DILATE--------膨胀操作
    // 第四个参数： 形态学运行的内核。若为NULL，表示3x3内核的中心
    // 第五个参数： 锚点 默认值Point(-1, -1)
    // 第六个参数： 迭代使用函数的次数，默认值1
    // 第七个参数： 推断图像外部像素的模中边界模式，默认值MORPH_CONSTANT,若改变畜产看文档
    // 第八个参数： 一般不用去管他，默认值morphologyDefaultBorderValue()
    morphologyEx(srcImage,
                 dstImage,
                 MORPH_GRADIENT,
                 element,
                 Point(-1, -1),
                 1,
                 BORDER_CONSTANT,
                 morphologyDefaultBorderValue());
    // 显示效果图
    imshow("<1>形态学操作【效果图】", dstImage);

    waitKey(0);
    return 0;
}
