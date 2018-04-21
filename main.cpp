#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 全局变量的定义及描述
Mat g_srcImage;
Mat g_dstBoxFilterImgage, g_dstBlurImage, g_dstGaussionImage;
Mat g_dstMediaImage, g_dstbilateraImage;

int g_nBoxFilter = 4;
int g_nBlur = 4;
int g_nGaussion = 4;
int g_nMedia = 4;
int g_nBilatera =4;

// 轨迹回调函数
void on_BoxFilter (int , void *) {
    boxFilter(g_srcImage,
              g_dstBoxFilterImgage,
              -1,
              Size(g_nBoxFilter + 1, g_nBoxFilter + 1));
    imshow("<1>方框滤波【效果图】", g_dstBoxFilterImgage);
}

void on_Blur (int , void *) {
    blur(g_srcImage,
         g_dstBlurImage,
         Size(g_nBlur + 1, g_nBlur + 1));
    imshow("<2>均值滤波【效果图】", g_dstBlurImage);
}

void on_Guassion (int , void *) {
    GaussianBlur(g_srcImage,
                 g_dstGaussionImage,
                 Size(g_nGaussion << 2 | 1, g_nGaussion << 2 | 1), // Size 必须是奇数
                 0, 0);

    imshow("<3>高斯滤波【效果图】", g_dstGaussionImage);
}

void on_Media (int , void *) {
    medianBlur(g_srcImage,
               g_dstMediaImage,
               g_nMedia << 2 | 1);  // 这个参数必须是大于1的奇数

    imshow("<4>中值滤波【效果图】", g_dstMediaImage);
}

void on_Bilatera (int , void *) {
    bilateralFilter(g_srcImage,
                    g_dstbilateraImage,
                    g_nBilatera,
                    g_nBilatera << 1,
                    g_nBilatera >> 1);

    imshow("<5>双边滤波【效果图】", g_dstbilateraImage);
}

int main (int argc, char *argv[]) {
    // 创建窗口
    namedWindow("<0>原始图像");
    // 读取原始图像，并显示
    g_srcImage = imread("../filter.jpg");
    imshow("<0>原始图像", g_srcImage);

    /* -----------方框滤波--------- */
    // 1. 创建方框滤波效果窗口
    namedWindow("<1>方框滤波【效果图】");
    // 2. 创建轨迹条
    createTrackbar("方框滤波", "<1>方框滤波【效果图】", &g_nBoxFilter, 40, on_BoxFilter, NULL);
    // 3. 初始化轨迹条
    on_BoxFilter(g_nBoxFilter, NULL);

    /* -----------均值滤波--------- */
    // 1. 创建均值滤波效果窗口
    namedWindow("<2>均值滤波【效果图】");
    // 2. 创建轨迹条
    createTrackbar("均值滤波", "<2>均值滤波【效果图】", &g_nBlur, 40, on_Blur);
    // 3. 初始化轨迹条
    on_Blur(g_nBlur, NULL);

    /* -----------高斯滤波--------- */
    // 1. 创建高斯滤波效果窗口
    namedWindow("<3>高斯滤波【效果图】");
    // 2. 创建轨迹条
    createTrackbar("高斯滤波", "<3>高斯滤波【效果图】", &g_nGaussion, 40, on_Guassion);
    // 3. 初始化轨迹条
    on_Guassion(g_nGaussion, NULL);

    /* -----------中值滤波--------- */
    // 1. 创建中值滤波效果窗口
    namedWindow("<4>中值滤波【效果图】");
    // 2. 创建轨迹条
    createTrackbar("中值滤波", "<4>中值滤波【效果图】", &g_nMedia, 40, on_Media);
    // 3. 初始化轨迹条
    on_Media(g_nMedia, NULL);

    /* -----------双边滤波--------- */
    // 1. 创建双边滤波效果窗口
    namedWindow("<5>双边滤波【效果图】");
    // 2. 创建轨迹条
    createTrackbar("双边滤波", "<5>双边滤波【效果图】", &g_nBilatera, 40, on_Bilatera);
    // 3. 初始化轨迹条
    on_Bilatera(g_nBilatera, NULL);

    waitKey(0);
    return 0;
}
