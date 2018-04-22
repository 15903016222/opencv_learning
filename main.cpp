#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    // 创建窗口 读取图片 显示原图
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../sobel.jpg");
    imshow("<0>【原图】", srcImage);

    // 创建gray_x gray_y矩阵
    Mat gray_x, gray_y;
    Mat abs_gray_x, abs_gray_y, dstImage;

    // 求 x 方向梯度
    // 描述：用于边缘检测的离散微分算子，利用高斯平滑和微分求导
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像深度
    // 第四个参数： X方向差分阶数
    // 第五个参数： Y方向差分阶数
    // 第六个参数： Sobel核的大小，必须是1，3， 5或7
    // 第七个参数： 计算导数值时可选的缩放因子，默认值1，表示默认情况下是没有应用缩放
    // 第八个参数： 结果存入目标图之前可选的delta值 默认值0
    // 第九个参数： 不用特别关心，使用默认值即可
    Sobel(srcImage,
          gray_x,
          CV_16S,
          1,
          0,
          3,
          1,
          0,
          BORDER_DEFAULT);
    // 先缩放元素再取绝对值，最后转换格式为8bit型
    convertScaleAbs(gray_x, abs_gray_x);
    imshow("<1>显示X方向的Sobel", abs_gray_x);

    // 求 y 方向梯度
    // 描述：用于边缘检测的离散微分算子，利用高斯平滑和微分求导
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像深度
    // 第四个参数： X方向差分阶数
    // 第五个参数： Y方向差分阶数
    // 第六个参数： Sobel核的大小，必须是1，3， 5或7
    // 第七个参数： 计算导数值时可选的缩放因子，默认值1，表示默认情况下是没有应用缩放
    // 第八个参数： 结果存入目标图之前可选的delta值 默认值0
    // 第九个参数： 不用特别关心，使用默认值即可
    Sobel(srcImage,
          gray_y,
          CV_16S,
          0,
          1,
          3,
          1,
          0,
          BORDER_DEFAULT);
    // 先缩放元素再取绝对值，最后转换格式为8bit型
    convertScaleAbs(gray_y, abs_gray_y);
    imshow("<2>显示Y方向的Sobel", abs_gray_y);

    // 合并梯度(近似)
    addWeighted(abs_gray_x, 0.5, abs_gray_y, 0.5, 0, dstImage);
    imshow("<3>【效果图】", dstImage);

    waitKey(0);

    return 0;
}
