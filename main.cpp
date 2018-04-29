#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【轮廓图】"

// 描述全局变量
Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int , void *) {
    // 对图像进行二值化，控制阀值
    threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);
    // 寻找轮廓
    findContours(g_thresholdImage_output,
                 g_vContours,
                 g_vHierarchy,
                 RETR_TREE,
                 CHAIN_APPROX_SIMPLE);
    // 遍历每个轮廓
    vector<vector<Point> > hull(g_vContours.size());
    for (unsigned int i = 0; i < hull.size(); ++i) {
        convexHull(Mat(g_vContours[i]), hull[i], false);
    }

    // 绘制轮廓和凸包
    Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
    for (int i = 0; i < g_vContours.size(); ++i) {
        Scalar color = Scalar(g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255),
                              g_rng.uniform(0, 255));
        drawContours(drawing,
                     g_vContours,
                     i,
                     color,
                     1,
                     LINE_AA);
        drawContours(drawing,
                     hull,
                     i,
                     color,
                     1,
                     LINE_AA);
    }
    cout << "count = " << g_vContours.size() << endl
         << "hull  = " << hull.size() << endl;

    imshow(WINDOW_NAME2, drawing);
}

int main( int argc, char** argv )
{
    g_srcImage = imread("../converx.jpg", 1);

    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    namedWindow(WINDOW_NAME1);
    imshow(WINDOW_NAME1, g_srcImage);

    createTrackbar("阀值", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);

    on_ThreshChange(g_nThresh, NULL);

    waitKey(0);

    return 0;
}
