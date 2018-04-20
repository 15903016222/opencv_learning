#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

// 轨迹条位置改变的调用的函数
void on_ContrastAndBright (int , void *) {
    namedWindow("原始窗口", 1);

    for (int y = 0; y < g_srcImage.rows; ++y) {
        for (int x = 0; x < g_srcImage.cols; ++x) {
            for (int c = 0; c < 3; ++c) {
                g_dstImage.at<Vec3b>(y, x)[c] =
                        saturate_cast<uchar>((g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
            }
        }
    }

    // 显示图像
    imshow("原始窗口", g_srcImage);
    imshow("效果窗口", g_dstImage);
}

int main (int argc, char *argv[]) {
    // 读取图像
    g_srcImage = imread ("../bright.jpg");
    if (!g_srcImage.data) {
        cout << "读取原始图像失败" << endl;
        return -1;
    }
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

    // 设置对比度，亮度值
    g_nBrightValue = 80;
    g_nContrastValue = 80;

    // 创建窗口
    // 第一个参数：窗口的名字
    // 第二个参数：1表示窗口大小无法改变调整
    //           0表示窗口可以改变调整
    namedWindow("效果窗口", 1);

    // 床架轨迹条
    // 第一个参数：轨迹条的名字
    // 第二个参数：轨迹条依附的窗口名字
    // 第三个参数：表示滑块的位置，创建时，滑块的初始位置就是该变量的值，当滑块的位置改变时，这个值也会改变
    // 第四个参数：滑块可以达到最大位置的值，最小值始终是0
    // 第五个参数：回调函数 默认值0
    // 第六个参数：void *默认值0 回调函数的需要的参数
    createTrackbar("对比度", "效果窗口", &g_nContrastValue, 300, on_ContrastAndBright);
    createTrackbar("亮  度", "效果窗口", &g_nBrightValue, 200, on_ContrastAndBright);

    // 回调函数初始化 结果在回调函数中显示
    // 这个函数必须初始化，否则回调函数就不会执行
    on_ContrastAndBright (g_nContrastValue, NULL);
    on_ContrastAndBright (g_nBrightValue, NULL);

    while ('q' != char (waitKey(1))) {
        ;
    }

    return 0;
}
