#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace std;

// 定义辅助宏
#define WINDOW_NAME1 "原始图"
#define WINDOW_NAME2 "效果图"

// 定义全局变量
Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_match (int , void *)
{
    // 定义局部变量
    Mat srcImage;
    g_srcImage.copyTo(srcImage);

    // 初始化用于结果输出的矩阵
    int result_rows = g_srcImage.rows - g_templateImage.rows + 1;
    int result_cols = g_srcImage.cols - g_templateImage.cols + 1;
    g_resultImage.create(result_rows, result_cols, CV_32FC1);

    // 进行匹配和标准化
    matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
    normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

    // 通过函数minMaxLoc定位最匹配的位置
    double minValue;
    double maxValue;
    Point  minLocation;
    Point  maxLocation;
    Point  matchLocation;

    minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

    // 对于方法SQDIFF 和 SQDIFF_NORMED，越小的数值有着更高的匹配结果。
    // 而其余的方法，数值越大匹配效果越好
    if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED) {
        matchLocation = minLocation;
    }
    else {
        matchLocation = maxLocation;
    }

    // 绘制出矩形，并显示最终结果
    rectangle(srcImage,
              matchLocation,
              Point(matchLocation.x + g_templateImage.cols,
                    matchLocation.y + g_templateImage.rows),
              Scalar(0, 0, 255),
              2,
              8,
              0);
    rectangle(g_resultImage,
              matchLocation,
              Point(matchLocation.x + g_templateImage.cols,
                    matchLocation.y + g_templateImage.rows),
              Scalar(0, 0, 255),
              2,
              8,
              0);

    cout << "matchPoint: " << matchLocation << endl;

    // 显示图像
    imshow(WINDOW_NAME1, srcImage);
    imshow(WINDOW_NAME2, g_resultImage);
}

int main (int argc, char *argv[])
{
    namedWindow(WINDOW_NAME1);
    namedWindow(WINDOW_NAME2);
    // 输入图像和模板图像，显示
    g_srcImage = imread("../match.jpg", 1);
    g_templateImage = imread("../matchTemplate.jpg", 1);

    // 创建滑动条并初始化
    createTrackbar("Method", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_match);
    on_match (g_nMatchMethod, NULL);

    waitKey(0);

    return 0;
}
