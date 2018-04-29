#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【轮廓图】"

// 定义全局变量
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

// 回调函数
void on_ThreshChange(int , void *) {
    // 边缘检测
    Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh < 1, 3);
    // 查找轮廓
    findContours(g_cannyMat_output,
                 g_vContours,
                 g_vHierarchy,
                 RETR_TREE,
                 CHAIN_APPROX_SIMPLE, Point(0, 0));
    Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
    for (int i = 0; i < g_vHierarchy.size(); ++i) {
        Scalar color = Scalar(g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255));
        // 绘制轮廓
        drawContours(drawing,
                     g_vContours,
                     i,
                     color,
                     2,
                     8,
                     g_vHierarchy,
                     0,
                     Point());
    }

    imshow(WINDOW_NAME2, drawing);
}

int main( int argc, char** argv )
{
    namedWindow(WINDOW_NAME1);
    g_srcImage = imread ("../google.jpg", 1);
    imshow(WINDOW_NAME1, g_srcImage);

    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    // 平滑处理
    blur(g_grayImage, g_grayImage, Size(3, 3));
    // 创建轨迹条
    createTrackbar("Canny阀值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
    // 初始化回调函数
    on_ThreshChange(g_nThresh, NULL);

    waitKey(0);

    return 0;
}
