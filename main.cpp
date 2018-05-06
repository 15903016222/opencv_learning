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
int g_nChangeNum = 16; // 像素变化的次数

bool verifySizes(RotatedRect mr)
{
    float error = 0.3;
    //Spain car plate size: 52x11 aspect 4,7272
    //China car plate size: 440mm*140mm，aspect 3.142857
    float aspect = 3.142857;
    //Set a min and max area. All other patchs are discarded
    int min= 1*aspect*1; // minimum area
    int max= 2000*aspect*2000; // maximum area
    //int min = 44 * 14 * m_verifyMin; // minimum area
    //int max = 44 * 14 * m_verifyMax; // maximum area
                                     //Get only patchs that match to a respect ratio.
    float rmin = aspect - aspect*error;
    float rmax = aspect + aspect*error;

    int area = mr.size.height * mr.size.width;
    float r = (float)mr.size.width / (float)mr.size.height;
    if (r < 1)
    {
        r = (float)mr.size.height / (float)mr.size.width;
    }

    if ((area < min || area > max) || (r < rmin || r > rmax))
    {
        return false;
    }
    else
    {
        return true;
    }
}

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


//    // 闭操作
//    Mat closeImage;
//    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
//    morphologyEx(g_edge, closeImage, MORPH_CLOSE, element);

//    // 定位车牌
//    for (int y = 0; y < closeImage.rows; ++y) {
//        int flags = 0;
//        uchar *data = closeImage.ptr<uchar>(y);
//        for (int x = 0; x < closeImage.cols - 1; ++x) {
//            if (0 != data[x] - data[x + 1]) {
//                ++flags;
//            }
//        }
//        if (flags >= 9) {
//           cout << "y: " << y << endl;
//        }
//    }

    Mat dstImage(g_edge.size(), g_edge.type());
    for (int y = 0; y < g_edge.rows; ++y) {
        int flags = 0;
        uchar *data = g_edge.ptr<uchar>(y);
        for (int x = 0; x < g_edge.cols; ++x) {
            if (255 == data[x]) {
                ++flags;
            }
        }
        if (flags > g_nChangeNum) {
            for (int i = 0; i < g_edge.cols; ++i) {
                dstImage.at<uchar>(y, i) = data[i];
            }
            cout << "y: " << y << endl;
        }
    }

    cout << "rows: " << g_edge.rows << endl
         << "cols: " << g_edge.cols << endl;

    imshow(WINDOW_NAME2, dstImage);

//    // 查找轮廓
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    findContours(g_edge, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

//    vector<vector<Point> > contours_poly(contours.size());
//    vector<Rect> boundRect(contours.size());

//    Mat contoursImage = Mat::zeros(g_edge.rows, g_edge.cols, CV_8UC3);

//    for (unsigned int i = 0; i < contours.size(); ++i) {
//        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
//        boundRect[i] = boundingRect(Mat(contours_poly[i]));
//    }

//    int index = 0;
//    for ( ; index >= 0; index = hierarchy[index][0]) {
//        Scalar color(255, 255, 255);
//        drawContours(contoursImage, contours, index, color, FILLED, LINE_AA, hierarchy);
//        rectangle(contoursImage, boundRect[index].tl(), boundRect[index].br(), color, 1, 8, 0);
//    }
//    cout << "contours.size: " << contours.size() << endl
//         << "hierarchy.size: " << hierarchy.size() << endl;
//    imshow(WINDOW_NAME2, contoursImage);

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
