#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建两个窗口
    namedWindow("方波滤波【原图】");
    // 读入图像,显示原图
    Mat srcImage = imread ("../boxfilter.jpg");
    imshow("方波滤波【原图】", srcImage);

    /* --------------方波滤波【boxFilter()】 */
    // 方波滤波操作
    Mat dstImage;
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： ddepth,输出图像深度，-1：表示使用的原始输入图像的深度
    // 第四个参数： 方波滤波的内核大小(方波大小)
    // 第五个参数： Point(w, h), 表示方波的中心：(-1, -1) 并且还是默认值
    // 第六个参数： normalize:是否矩阵归一化，默认值true
    // 第七个参数： borderType:一般不需要设置，使用默认值即可
    boxFilter(srcImage, dstImage, -1, Size(3, 3)/*, Point(-1, -1), true, BORDER_DEFAULT*/);

    // 显示效果图
    namedWindow("方波滤波【效果图】");
    imshow("方波滤波【效果图】", dstImage);

    /* ---------均值滤波[blur()]-------------- */
    Mat blurImage;
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 内核大小
    // 第四个参数： 表示锚点，表示需要平滑的那个点
    // 第五个参数： 一般使用默认的，不要太关心
    blur(srcImage, blurImage, Size(3, 3), Point(-1, -1)/*, BORDER_DEFAULT*/);

    // 显示均值滤波
    namedWindow("均值滤波【效果图】");
    imshow("均值滤波【效果图】", blurImage);

    waitKey(0);
    return 0;
}
