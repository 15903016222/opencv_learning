#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 全局变量声明
// 原始图像 创建3个不同线性滤波的输出图像
Mat srcImage, g_dstBoxFilter, g_dstBlur, g_dstGaussionBlur;
int g_nBoxFilter = 3;       // 方框滤波内核参数大小
int g_nBlur = 3;            // 均值滤波内核参数大小
int g_nGaussionBlur = 3;    // 高斯滤波内核参数大小

// 3个轨迹条的回调函数
void on_BoxFilter (int , void *) {
    boxFilter(srcImage,
              g_dstBoxFilter,
              -1,
              Size(g_nBoxFilter + 1, g_nBoxFilter + 1)
              /*, Point(-1, -1), true, BORDER_DEFAULT*/); // 注释的都是默认值

    imshow("方框滤波【效果图】", g_dstBoxFilter);
}

void on_Blur (int , void *) {
    blur(srcImage, g_dstBlur,
         Size(g_nBlur + 1, g_nBlur + 1)
         /*, Point(-1, -1), BORDER_DEFAULT*/); // 注释的都是默认值

    imshow("均值滤波【效果图】", g_dstBlur);
}

void on_GaussionBlur (int , void *) {
    GaussianBlur(srcImage,
                 g_dstGaussionBlur,
                 Size(g_nGaussionBlur << 1 | 1, g_nGaussionBlur << 1 | 1), // 高斯滤波的内核大小必须是奇数
                 0,
                 0/*, BORDER_DEFAULT*/);

    imshow("高斯滤波【效果图】", g_dstGaussionBlur);
}

int main (int argc, char *argv[]) {
    // 创建原图窗口 3个滤波窗口
    namedWindow("【原图】");
    namedWindow("方框滤波【效果图】");
    namedWindow("均值滤波【效果图】");
    namedWindow("高斯滤波【效果图】");

    // 读入图像,显示原图
    srcImage = imread ("../boxfilter.jpg");
    imshow("【原图】", srcImage);

    // 创建3个轨迹条
    createTrackbar("方框滤波", "方框滤波【效果图】", &g_nBoxFilter, 40, on_BoxFilter, NULL);
    createTrackbar("均值滤波", "均值滤波【效果图】", &g_nBlur, 40, on_Blur, NULL);
    createTrackbar("高斯滤波", "高斯滤波【效果图】", &g_nGaussionBlur, 40, on_GaussionBlur, NULL);

    // 初始化3个轨迹条
    on_BoxFilter(g_nBoxFilter, NULL);
    on_Blur(g_nBlur, NULL);
    on_GaussionBlur(g_nGaussionBlur, NULL);

    waitKey(0);
    return 0;
}
