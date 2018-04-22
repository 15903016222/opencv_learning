#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 定义全局变量信息
int g_nThresholdValue = 100;
int g_nThresholdType = 3; // 0 THRES_BINARY ---------- 二进制阀值化
                          // 1 THRES_BINARY_INV ------ 反向二进制阀值化并翻转
                          // 2 THRES_TRUNC ----------- 截断阀值化
                          // 3 THRES_TOZERO ---------- 超过阀值被置为0
                          // 4 THRES_TOZERO_INV ------ 低于阀值被置为0
Mat g_srcImage, g_grayImage, g_dstImage;

// 定义回调函数
void on_Threshold (int , void *) {
    threshold(g_srcImage,
              g_dstImage,
              g_nThresholdValue,
              255,
              g_nThresholdType);

    imshow ("<1>【效果图】", g_dstImage);
}

int main( int argc, char** argv )
{
    // 创建窗口 读取图片 显示原图
    namedWindow("<0>【原图】");
    g_srcImage = imread ("../threshold.jpg");
    imshow("<0>【原图】", g_srcImage);

    // 创建灰度图窗口，生成灰度图
    namedWindow("<1>【效果图】");
    cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
    imshow("<1>【效果图】", g_grayImage);

    // 创建轨迹条，初始化回调函数
    createTrackbar("模  式",
                   "<1>【效果图】",
                   &g_nThresholdType,
                   4,
                   on_Threshold);
    createTrackbar("参数值",
                   "<1>【效果图】",
                   &g_nThresholdValue,
                   255,
                   on_Threshold);

    on_Threshold(g_nThresholdValue, NULL);

    waitKey(0);

    return 0;
}
