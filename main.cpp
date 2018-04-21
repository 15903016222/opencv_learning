#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 定义全局变量信息
Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT; // MORPH_RECT->矩形， MORPH_CROSS->十字架, MORPH_ELLIPSE->椭圆
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;

// 定义回调函数
void on_OpenClose (int , void *) {
    // 偏移量定义
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;
    int Absolute_offset = offset > 0 ? offset : -offset;

    // 自定义核
    Mat element = getStructuringElement(g_nElementShape,
                                        Size(Absolute_offset << 1 | 1, Absolute_offset << 1 | 1),
                                        Point(Absolute_offset, Absolute_offset));

    // 形态学操作
    if (offset < 0) {
        // 开运算
        morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
        imshow ("<1>开运算/闭运算", g_dstImage);
    } else {
        // 闭运算
        morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
        imshow ("<1>开运算/闭运算", g_dstImage);
    }

}

void on_ErodeDilate (int , void *) {
    int offset = g_nErodeDilateNum - g_nMaxIterationNum;
    int Absolute_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(g_nElementShape,
                                        Size(Absolute_offset << 1 | 1, Absolute_offset << 1 | 1),
                                        Point(Absolute_offset, Absolute_offset));

    if (offset < 0) {
        // 腐蚀操作
        morphologyEx(g_srcImage, g_dstImage, MORPH_ERODE, element);
        imshow("<2>腐蚀/膨胀运算", g_dstImage);
    } else {
        // 膨胀操作
        morphologyEx(g_srcImage, g_dstImage, MORPH_DILATE, element);
        imshow("<2>腐蚀/膨胀运算", g_dstImage);
    }
}

void on_TopBlackHat (int , void *) {
    int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
    int Absolute_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(g_nElementShape,
                                        Size(Absolute_offset << 1 | 1, Absolute_offset << 1 | 1),
                                        Point(Absolute_offset, Absolute_offset));
    if (offset < 0) {
        // 顶帽操作
        morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
        imshow("<3>顶帽/黑帽运算", g_dstImage);
    } else {
        // 黑帽操作
        morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
        imshow("<3>顶帽/黑帽运算", g_dstImage);
    }
}

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("<0>【原图】");
    namedWindow("<1>开运算/闭运算");
    namedWindow("<2>腐蚀/膨胀运算");
    namedWindow("<3>顶帽/黑帽运算");

    // 读取原始图
    g_srcImage = imread ("../America.jpg");
    imshow ("<0>【原图】", g_srcImage);

    // 创建轨迹条
    createTrackbar("迭代值",
                   "<1>开运算/闭运算",
                   &g_nOpenCloseNum,
                   g_nMaxIterationNum << 1 | 1,
                   on_OpenClose);
    createTrackbar("内核形状",
                   "<1>开运算/闭运算",
                   &g_nElementShape,
                   1 << 1,
                   on_OpenClose);
    createTrackbar("迭代值",
                   "<2>腐蚀/膨胀运算",
                   &g_nErodeDilateNum,
                   g_nMaxIterationNum << 1 | 1,
                   on_ErodeDilate);
    createTrackbar("内核形状",
                   "<2>腐蚀/膨胀运算",
                   &g_nElementShape,
                   1 << 1,
                   on_ErodeDilate);
    createTrackbar("迭代值",
                   "<3>顶帽/黑帽运算",
                   &g_nTopBlackHatNum,
                   g_nMaxIterationNum << 1 | 1,
                   on_TopBlackHat);
    createTrackbar("内核形状",
                   "<3>顶帽/黑帽运算",
                   &g_nElementShape,
                   1 << 1,
                   on_TopBlackHat);

    // 回调函数初始化
    on_OpenClose(g_nOpenCloseNum, NULL);
    on_ErodeDilate(g_nErodeDilateNum, NULL);
    on_TopBlackHat(g_nTopBlackHatNum, NULL);

    waitKey(0);
    return 0;
}
