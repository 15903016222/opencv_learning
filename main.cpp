#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_mat;

int g_RedNum   = 0;
int g_GreenNum = 0;
int g_BlueNum  = 0;

void onMouse (int event, int x, int y, int, void *) {
    cout << "count: " << event << endl
         << "x: " << x << endl
         << "y: " << y << endl;
}

void showColor () {
    for (int x = 0; x < g_mat.rows; ++x) {
        for (int y = 0; y < g_mat.cols; ++y) {
            g_mat.at<Vec3b>(x, y)[0] = g_BlueNum;
            g_mat.at<Vec3b>(x, y)[1] = g_GreenNum;
            g_mat.at<Vec3b>(x, y)[2] = g_RedNum;
        }
    }

    imshow("ColorBar", g_mat);
}

void on_Red (int , void *) {
    showColor();
}

void on_Green (int , void *) {
    showColor();
}

void on_Blue (int , void *) {
    showColor();
}

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("ColorBar");
    g_mat = Mat(480, 480, CV_8UC3);

    setMouseCallback("ColorBar", onMouse, NULL);

    // 创建轨迹条
    createTrackbar("R", "ColorBar", &g_RedNum,255, on_Red);
    createTrackbar("G", "ColorBar", &g_GreenNum, 255, on_Green);
    createTrackbar("B", "ColorBar", &g_BlueNum, 255, on_Blue);

    // 初始化轨迹条函数
    on_Red(g_RedNum, NULL);
    on_Green(g_GreenNum, NULL);
    on_Blue(g_BlueNum, NULL);

    waitKey(0);
    return 0;
}
