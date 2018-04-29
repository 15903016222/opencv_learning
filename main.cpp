#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【效果图】"

// 定义全局变量信息
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50;     // 阀值
int g_nMaxThresh = 255; // 最大阀值
RNG g_rng (12345);

// 回调函数
void on_ContoursChange(int , void *) {
    // 定义了参数
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    // 图片二值化
    threshold(g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY);
    // 找出轮廓
    findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    // 多边形逼近轮廓 + 获取矩形和圆形边界框
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> centor(contours.size());
    vector<float> radius(contours.size());

    // 循环遍历所有部分，进行本程序最核心的操作
    for (unsigned i = 0; i < contours.size(); ++i) {
        // 用指定精度逼近多边形曲线
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        // 计算点集最外面的矩形边界
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        // 对给定的2D点集，寻找最小面积的包围圆形
        minEnclosingCircle(contours_poly[i], centor[i], radius[i]);
    }

    // 绘制多边形轮廓 + 包围的矩形 + 圆形框
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (unsigned int i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255));
        drawContours(drawing, contours_poly, i, color, 1, LINE_AA);

        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, LINE_AA, 0);

        circle(drawing, centor[i], radius[i], color, 2, LINE_AA, 0);
    }

    namedWindow(WINDOW_NAME2);
    imshow(WINDOW_NAME2, drawing);
}

int main( int argc, char** argv )
{
    g_srcImage = imread("../sea.jpg", 1);
    imshow(WINDOW_NAME1, g_srcImage);

    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    // 平滑操作
    blur(g_grayImage, g_grayImage, Size(3, 3));

    namedWindow(WINDOW_NAME2);
    createTrackbar("阀值", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ContoursChange);

    on_ContoursChange(g_nThresh, NULL);

    waitKey();

    return 0;
}
