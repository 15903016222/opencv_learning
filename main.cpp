#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 定义全局变量
Mat g_srcImage, g_srcGrayImage, g_dstImage;

Mat g_cannyDetecteEdges;
int g_cannyLowThreshold = 1;

Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;

Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

// 回调函数
void on_Canny (int , void *) {
    // 滤波
    blur(g_srcGrayImage, g_cannyDetecteEdges, Size(3, 3));

    // 运行Canny算子
    Canny(g_cannyDetecteEdges, g_cannyDetecteEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

    g_dstImage = Scalar::all(0);
    g_srcImage.copyTo(g_dstImage, g_cannyDetecteEdges);

    // 显示
    imshow("<1>Canny【效果图】", g_dstImage);
}

void on_Sobel (int , void *) {
    // Sobel算子
    Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (g_sobelKernelSize << 1 | 1), 1, 0);
    convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X);

    Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (g_sobelKernelSize << 1 | 1), 1, 0);
    convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);

    addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);

    // 显示
    imshow("<2>Sobel【效果图】", g_dstImage);
}

void Scharr1 () {
    // 求X方向的梯度
    Scharr(g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0);
    convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);

    // 求Y方向的梯度
    Scharr(g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0);
    convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);

    // 叠加
    addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

    // 显示
    imshow("<3>Scharr【效果图】", g_dstImage);
}

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    g_srcImage = imread ("../edges.jpg");
    imshow("<0>【原图】", g_srcImage);

    g_dstImage.create(g_srcImage.size(), g_srcImage.type());
    cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);

    namedWindow("<1>Canny【效果图】");
    namedWindow("<2>Sobel【效果图】");

    createTrackbar("参数值", "<1>Canny【效果图】", &g_cannyLowThreshold, 120, on_Canny);
    createTrackbar("参数值", "<2>Sobel【效果图】", &g_sobelKernelSize, 3, on_Sobel);

    on_Canny(0, NULL);
    on_Sobel(0, NULL);
    Scharr1();

    waitKey(0);

    return 0;
}
