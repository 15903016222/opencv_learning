#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 定义全局变量
Mat g_srcImage, g_dstImage, g_midImage;

// 接受TrackBar位置
int g_nthreashold = 100;
int g_ncanny = 50;

void on_Hough (int , void *)
{
    Mat dstImage = g_dstImage.clone();
    vector<Vec4i> lines;
    // 描述： 霍夫线性变换
    // 第一个参数： 输入图像
    // 第二个参数： 存放检测到线的存储器
    // 第三个参数： 以像素为单位的最小精度
    // 第四个参数： 弧度
    // 第五个参数： 检测到累加器的阀值
    // 第六个参数： 最小长度
    // 第七个参数： 默认参数
    HoughLinesP(g_midImage,
                lines,
                1,
                CV_PI / 180,
                g_nthreashold + 1,
                20,
                0);
    for (size_t i = 0; i < lines.size(); ++i) {
        Vec4i l = lines[i];
        line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1);
    }
    imshow("<1>【效果图】", dstImage);
    cout << "size = " << lines.size() << endl;
}

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    namedWindow("<1>【效果图】");
    Mat g_srcImage = imread ("../hough.jpg");
    imshow("<0>【原图】", g_srcImage);

    createTrackbar("位置", "<1>【效果图】", &g_nthreashold, 200, on_Hough, 0);

    Canny(g_srcImage, g_midImage, 100, 200, 3);
    cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR);

    on_Hough(g_nthreashold, NULL);

    waitKey(0);

    return 0;
}
