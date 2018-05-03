#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【效果图】"

// 定义全局变量
int blockSize = 5;
int constValue;
Mat g_srcImage;
Mat g_gaussianFillImage, g_sobelImage;
Mat g_threshImage, g_closeImage;
int g_nElementShape = MORPH_RECT;
// 变量接收的TrackBar位置的参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;

Mat sobeproc(const Mat &src);
void on_OpenClose(int , void *);
void on_Trackbar(int, void *);

int main (int argc, char *argv[])
{
    // 读取原图 显示
    namedWindow(WINDOW_NAME1);
    g_srcImage = imread("../car.jpg", 0);
    imshow(WINDOW_NAME1, g_srcImage);
    GaussianBlur(g_srcImage, g_gaussianFillImage, Size(5, 5), 0, 0);
    g_sobelImage = sobeproc(g_gaussianFillImage);
    constValue = 10;
    g_nOpenCloseNum = 9;
    createTrackbar("threshold", WINDOW_NAME1, &constValue, 100, on_Trackbar);
    createTrackbar("迭代值", WINDOW_NAME1, &g_nOpenCloseNum, g_nMaxIterationNum * 10 + 1, on_OpenClose);

    on_Trackbar(0, NULL);
    on_OpenClose(0, NULL);

    waitKey(0);
    return 0;
}

Mat sobeproc(const Mat &src)
{
    Mat dst;
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

    Sobel(src, grad_x, CV_8U, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    Sobel(src, grad_y, CV_8U, 0, 1, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.6, abs_grad_y, 0.4, 0, dst);

    return dst;
}

void on_Trackbar(int, void *)
{
    adaptiveThreshold(g_sobelImage, g_threshImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
    imshow(WINDOW_NAME1, g_threshImage);
}

void on_OpenClose(int, void *)
{
    // 偏移量定义
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;
    int Absolute_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(g_nElementShape,
                                        Size(Absolute_offset * 2 + 1,
                                             Absolute_offset * 2 +1),
                                        Point(Absolute_offset,
                                              Absolute_offset));
    if (offset < 0) {
        morphologyEx(g_threshImage, g_closeImage, MORPH_OPEN, element);
    }
    else {
        morphologyEx(g_threshImage, g_closeImage, MORPH_CLOSE, element);
    }

    imshow(WINDOW_NAME1, g_closeImage);
}
