#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【效果图】"

int main( int argc, char** argv )
{
    Mat srcImage, hsvImage;

    srcImage = imread("../cup.jpg");
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
    imshow(WINDOW_NAME1, srcImage);

    // 参数准备
    int hueBinNum = 30;
    int saturationBinNum = 32;
    int histSize[] = {hueBinNum, saturationBinNum};
    float hueRanges[] = {0, 180};
    float saturationRanges[] = {0, 256};
    const float *ranges[] = {hueRanges, saturationRanges};
    MatND dstHist;
    int channels[] = {0, 1};

    // 正式调用calcHist，进行直方图计算
    // 描述： 计算直方图
    // 第一个参数： 输入数组(或数组集)
    // 第二个参数： 输入数组的个数
    // 第三个参数： 需要统计的通道索引
    // 第四个参数： 可选的操作掩码
    // 第五个参数： 输出直方图目标
    // 第六个参数： 需要计算的直方图纬度
    // 第七个参数： 存放每个纬度的直方图尺寸的数组
    // 第八个参数： 表示每一个纬度数组
    // 第九个参数： 指示直方图是否均匀的标示符
    // 第十个参数： 累计标示符
    calcHist(&hsvImage,
             1,
             channels,
             Mat(),
             dstHist,
             2,
             histSize,
             ranges,
             true,
             false);

    // 为绘制直方图准备参数
    double maxValue = 0;
    // 描述： 在数组中找到全局的最小值和最大值
    // 第一个参数： 输入单通道阵列
    // 第二个参数： 返回最小值的指针
    // 第三个参数： 返回最大值指针
    // 第四个参数： 返回最小位置的指针
    // 第五个参数： 返回最大位置的指针
    // 第六个参数： 用于选择子阵列的可选掩膜
    minMaxLoc(dstHist, 0, &maxValue, 0, 0);
    int scale = 10;
    Mat histImg = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);

    // 双层循环，进行直方图的绘制
    for (int hue = 0; hue < hueBinNum; ++hue) {
        for (int saturation = 0; saturation < saturationBinNum; ++saturation) {
            float binValue = dstHist.at<float>(hue, saturation);
            int intensity = cvRound(binValue * 255 / maxValue);

            // 正式绘制
            rectangle(histImg,
                      Point(hue * scale, saturation * scale),
                      Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
                      Scalar::all(intensity),
                      FILLED);
        }
    }

    // 显示效果图
    imshow(WINDOW_NAME2, histImg);

    waitKey(0);

    return 0;
}
