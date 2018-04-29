#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../contours.jpg", 0);
    imshow("<0>【原图】", srcImage);

    namedWindow("<1>【效果图】");
    Mat dstImage = Mat::zeros(srcImage.size(), CV_8UC3);

    srcImage = srcImage > 119;
    imshow("取阀值后的原始图", srcImage);

    // 定义轮廓和层次结构
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // 查找轮廓
    // 描述： 用于在二值图像中寻找轮廓
    // 第一个参数： 输入图像，需为8位的单通道图像，即灰度图
    // 第二个参数： 存放检测到的轮廓 每个轮廓存储为一个点向量，类型vector<vector<Point> >
    // 第三个参数： 可选输出向量，包含图像的拓布信息，每个轮廓包含4个hierarchy[i][0] ~ hierarchy[i][3]
    //            后一个轮廓，前一个轮廓， 父轮廓，内嵌轮廓编号
    // 第四个参数： 轮廓检测模式，
    // 第五个参数： 轮廓的近似办法
    findContours(srcImage,
                 contours,
                 hierarchy,
                 RETR_CCOMP,
                 CHAIN_APPROX_SIMPLE);

    // 遍历所有顶层的轮廓
    int index = 0;
    for ( ; index >= 0; index = hierachy[index][0]) {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        // 描述： 绘制轮廓信息
        // 第一个参谋： 目标图像
        // 第二个参数： 输入的轮廓
        // 第三个参数： 轮廓绘制的只是变量
        // 第四个参数： 绘制轮廓的颜色
        // 第五个参数： 轮廓线条的粗细度
        // 第六个参数： 线条类型
        // 第七个参数： 可选的层次结构
        // 第八个参数： 绘制轮廓的最大等级
        // 第九个参数： 可选轮廓的偏移参数
        drawContours(dstImage,
                     contours,
                     index,
                     color,
                     FILLED,
                     LINE_8,
                     hierarchy);
    }

    // 显示最后的轮廓图
    imshow("<1>【效果图】", dstImage);

    waitKey(0);

    return 0;
}
