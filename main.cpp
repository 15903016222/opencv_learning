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

bool verifySizes(RotatedRect mr);

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

    // 查找轮廓
    // 准备参数
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(g_closeImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());

    for (unsigned int i = 0; i < contours.size(); ++i) {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
    }

    Mat drawing = Mat::zeros(g_closeImage.size(), CV_8UC3);
    for (unsigned int i = 0; i < contours.size(); ++i) {
//        Scalar color = Scalar(theRNG().uniform(0, 255),
//                              theRNG().uniform(0, 255),
//                              theRNG().uniform(0, 255));
        Scalar color = Scalar(255, 255, 255);
        drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, 4, 0);
    }

    imshow(WINDOW_NAME1, drawing);
}

//-----------------------------------【verifySizes函数】----------------------------------
//		描述：判断是否为车牌区域
//-----------------------------------------------------------------------------------------------
bool verifySizes(RotatedRect mr)
{
    float error = 0.4;
    //Spain car plate size: 52x11 scale 4,7272
    float scale = 3.667;
    //Set a min and max area. All other patchs are discarded
    int min = 150 * scale *100; // minimum area
    int max = 200 * scale * 200; // maximum area
                                 //Get only patchs that match to a respect ratio.
    float rmin = scale - scale*error;
    float rmax = scale + scale*error;

    int area = mr.size.height * mr.size.width;
    float r = (float)mr.size.width / (float)mr.size.height;
    if (r<1)
        r = (float)mr.size.height / (float)mr.size.width;

    if ((area < min || area > max) || (r < rmin || r > rmax)) {
        return false;
    }
    else {
        return true;
    }

}
