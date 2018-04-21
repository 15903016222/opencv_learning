#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 定义全局变量信息
Mat g_srcImage, g_dstImage;
int g_nTrackBarNum = 1;
int g_nElementSizeChanges = 3;

void process () {
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(g_nElementSizeChanges << 1 | 1, g_nElementSizeChanges << 1 | 1),
                                        Point(g_nElementSizeChanges, g_nElementSizeChanges));

    if (!g_nTrackBarNum) {
        // 膨胀操作
        dilate(g_srcImage, g_dstImage, element);
    } else {
        // 腐蚀操作
        erode(g_srcImage, g_dstImage, element);
    }

    imshow("<1>膨胀/腐蚀【效果图】", g_dstImage);
}

// 定义回调函数
void on_TrackBarChange (int , void *) {
    process();
}

void on_ElemnetChange (int , void *) {
    process();
}

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("<0>原始图像");
    // 读取原始图像，并显示
    g_srcImage = imread("../dilate_erode.jpg");
    imshow("<0>原始图像", g_srcImage);

    // 获取自定义内核信息
    Mat element =
            getStructuringElement(MORPH_RECT,
                                  Size(g_nElementSizeChanges << 1 | 1, g_nElementSizeChanges << 1 | 1),
                                  Point(g_nElementSizeChanges, g_nElementSizeChanges));

    // 腐蚀操作
    erode(g_srcImage, g_dstImage, element);
    // 显示操作图
    namedWindow("<1>膨胀/腐蚀【效果图】");

    // 创建轨迹条
    createTrackbar("膨胀/腐蚀", "<1>膨胀/腐蚀【效果图】", &g_nTrackBarNum, 1, on_TrackBarChange);
    createTrackbar("内核尺寸", "<1>膨胀/腐蚀【效果图】", &g_nElementSizeChanges, 40, on_ElemnetChange);

    // 初始化回调函数
    on_TrackBarChange(g_nTrackBarNum, NULL);
    on_ElemnetChange(g_nElementSizeChanges, NULL);

    waitKey(0);
    return 0;
}
