#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【效果图】"

// 全局变量信息
Mat g_srcImage, g_grayImage, g_gaussianImage, g_threshImage;
Mat g_edge;
int g_nThresh = 165;
int g_nMaxThresh = 255;
int g_nChangeNum = 0; // 像素变化的次数

void on_callback(int , void *)
{
    // 灰度化，平滑，降噪，二值化，边缘检测
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    //blur(g_grayImage, g_grayImage, Size(3, 3), Point(0, 0), BORDER_DEFAULT);

    GaussianBlur(g_grayImage, g_gaussianImage, Size(5, 5), 0, 0);

    threshold(g_gaussianImage, g_threshImage, g_nThresh, 255, THRESH_BINARY);

    Canny(g_threshImage, g_edge, 3, 9, 3);

//    // Sobel
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;

//    //X方向
//    Sobel(g_threshImage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
//    convertScaleAbs(grad_x, abs_grad_x);

//    //Y方向
//    Sobel(g_threshImage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
//    convertScaleAbs(grad_y, abs_grad_y);

//    //合并
//    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, g_edge);

    Mat dstImage(g_edge.size(), g_edge.type());
    int rows[562] = {0};
    for (int y = 0; y < g_edge.rows; ++y) {
        int flags = 0;
        uchar *data = g_edge.ptr<uchar>(y);
        for (int x = 0; x < g_edge.cols - 1; ++x) {
            if (0 != data[x] - data[x + 1]) {
                ++flags;
            }
            if (flags > 18) {
                rows[y] = 1;
            }
            else {
                rows[y] = 0;
            }
        }
    }

    int same[562][3] = {0};
    int flag  = 0;
    int count = 0;
    for (int i = 0; i < g_edge.rows - 1; ++i) {
        if ((0 == rows[i] - rows[i + 1]) && (1 == rows[i])) {
            if (!flag) {
                same[count][1] = i;
            }
            else {
                same[count][2] = i;
            }
            same[count][0] = ++flag;
        }
        else {
            flag = 0;
            if (same[count][0]) {
                ++count;
            }
        }
    }

    int max = 0;
    int tmp = 0;
    for (int i = 0; i < 562; ++i) {
        if (max <= same[i][0]) {
            max = same[i][0];
            tmp = i;
        }
    }

    for (int y = 0; y < g_edge.rows; ++y) {
        if (y >= same[tmp][1] - 5 && y <= same[tmp][2] + 5) {
            continue;
        }
        uchar *data = g_edge.ptr<uchar>(y);
        for (int x = 0; x < g_edge.cols; ++x) {
            data[x] = 0;
        }
    }

    // 计算长度
    int width = same[tmp][0] * 3.14;


    cout << "rows: " << g_edge.rows << endl
         << "cols: " << g_edge.cols << endl;

    imshow(WINDOW_NAME2, g_edge);

}

int main (int argc, char *argv[])
{
    // 读取图像
    namedWindow(WINDOW_NAME1);
    g_srcImage = imread("../car.jpg", 1);
    imshow(WINDOW_NAME1, g_srcImage);

    createTrackbar("thresh", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_callback);
    createTrackbar("counts", WINDOW_NAME1, &g_nChangeNum, 750, on_callback);
    // 车牌号分割

    // 模板匹配

    // 识别车牌号

    on_callback(0, NULL);

    waitKey(0);

    return 0;
}
