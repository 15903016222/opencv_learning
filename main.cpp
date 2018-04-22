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

    // 描述：resize()调整图像大小函数
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像，当其非零时，由第三个参数dsize决定 或者 由src.size()决定
    // 第三个参数： 输出图像的大小，如果等于0，由dsize = Size(round(fx*src.cols), round(fy*src.rows))
    // 第四个参数： 沿水平轴的缩放系数
    // 第五个参数： 沿垂直轴的缩放系数
    // 第六个参数： 指定插值方式，默认INTER_LINEAR---线性插值
    resize(srcImage,
           dstImage1,
           Size(srcImage.cols >> 1, srcImage.rows >> 1),
           0,
           0,
           3);
    imshow ("<1>【效果图】", dstImage1);
    resize(srcImage,
           dstImage2,
           Size(srcImage.cols << 1, srcImage.rows << 1),
           0,
           0,
           3);
    imshow ("<2>【效果图】", dstImage2);

    waitKey(0);
    return 0;
}
