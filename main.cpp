#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建原图窗口
    namedWindow("【原图】");
    // 读入图像,显示原图
    Mat srcImage = imread ("../boxfilter.jpg");
    imshow("【原图】", srcImage);

    /* --------------方波滤波【boxFilter()】 */
    // 方波滤波操作
    Mat dstImage;
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： ddepth,输出图像深度，-1：表示使用的原始输入图像的深度
    // 第四个参数： 方波滤波的内核大小(方波大小)
    // 第五个参数： Point(w, h), 表示方波的中心：(-1, -1) 并且还是默认值
    // 第六个参数： normalize:是否矩阵归一化，默认值true
    // 第七个参数： borderType:一般不需要设置，使用默认值即可
    boxFilter(srcImage, dstImage, -1, Size(3, 3)/*, Point(-1, -1), true, BORDER_DEFAULT*/);

    // 显示效果图
    namedWindow("方波滤波【效果图】");
    imshow("方波滤波【效果图】", dstImage);

    /* ---------均值滤波[blur()]-------------- */
    Mat blurImage;
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 内核大小
    // 第四个参数： 表示锚点，表示需要平滑的那个点
    // 第五个参数： 一般使用默认的，不要太关心
    blur(srcImage, blurImage, Size(3, 3), Point(-1, -1)/*, BORDER_DEFAULT*/);

    // 显示均值滤波
    namedWindow("均值滤波【效果图】");
    imshow("均值滤波【效果图】", blurImage);

    /* -------------高斯滤波GaussionBlur()---------- */
    Mat gaussionImage;
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 内核大小
    // 第四个参数： 高斯函数在X方向的标准偏差
    // 第五个参数： 高斯函数在Y方向的标准偏差 默认值0
    //            若X，Y都为0， 那么就由ksize.width ksize.height计算出来
    // 第六个参数： 使用默认值，一般不用太关心这个参数
    GaussianBlur(srcImage, gaussionImage, Size(3, 3), 0, 0/*, BORDER_DEFAULT*/);

    // 显示高斯滤波操作
    namedWindow("高斯滤波【效果图】");
    imshow("高斯滤波【效果图】", gaussionImage);

    waitKey(0);
    return 0;
}
