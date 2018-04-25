#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../houghcircle.jpg");
    imshow("<0>【原图】", srcImage);

    namedWindow("<1>临时图片");
    namedWindow("<2>【效果图】");

    Mat midImage, dstImage;
    // 颜色灰度转换
    cvtColor(srcImage, midImage, COLOR_BGR2GRAY);

    // 高斯模糊转换
    GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

    // 检测圆
    vector<Vec3f> circles;
    // 描述： 霍夫梯度法，霍夫圆变换
    // 第一个参数： 输入图像
    // 第二个参数： 存储检测圆的输出矢量
    // 第三个参数： 使用的检测方法，目前只是用HOUGH_GRADIENT
    // 第四个参数： 用来检测圆心的累加器图像的分辨率与输入图像之比的倒数，dp=1 累加器和输入图像具有相同的分辨率
    //                                                         dp=2 累加器便有输入图像的一半大的宽度和高度
    // 第五个参数： 霍夫变换检测到的圆的圆心之间的最小距离，这个参数很小的话，多个相邻的圆被错误的检测成一个重合的圆，
    //                                             反之，有些圆就检测不出来
    // 第六个参数： 表示传递给Canny边缘检测算子的高阀值，低阀值则为高阀值的一半
    // 第七个参数： 检测圆心累加器的阀值，它越小，就越可以检测到更多根本不存在的圆，越大，能通过检测的圆就更加接近完美的圆
    // 第八个参数： 默认值0 圆半径的最小值
    // 第九个参数： 默认值0 圆半径的最大值
    HoughCircles(midImage,
                 circles,
                 HOUGH_GRADIENT,
                 1.5,
                 10,
                 200,
                 100,
                 0,
                 0);

    for (size_t i = 0; i < circles.size(); ++i) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle(srcImage, center, 3, Scalar(0, 0, 255), -1, LINE_8, 0);
        circle(srcImage, center, radius, Scalar(155, 50, 255), 3, LINE_8, 0);
    }

    imshow("<1>临时图片", midImage);
    imshow("<2>【效果图】", srcImage);

    waitKey(0);

    return 0;
}
