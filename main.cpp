#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool MultiChannelBlending () {
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;
    Mat imageBlueChannel, imageGreenChannel, imageRedChannel;

    // 读入图像
    srcImage = imread("../dota_jugg.jpg");
    logoImage = imread("../dota_logo.jpg", 0);

    // 分离图像通道
    // 第一个参数：需要进行分离的多通道数组Mat
    // 第二个参数：需要输出的数组或者vector容器
    split(srcImage, channels); // 分离彩色通道
    // 取图像的每个通道的分量
    imageBlueChannel  = channels.at(0);
    imageGreenChannel = channels.at(1);
    imageRedChannel   = channels.at(2);

    // 定义ROI区域
    Mat imageROIBlue  = imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows));
    Mat imageROIGreen = imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows));
    Mat imageROIRed   = imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows));

    // 线性区域权重叠加
    // 多通道合成图像
    // 显示
    // Blue 通道混合
    addWeighted(imageROIBlue, 1.0, logoImage, 0.5, 0.0, imageROIBlue);
    // 第一个参数：需要被合并的输入矩阵，或者vector向量
    // 第二个参数：输出矩阵
    merge(channels, srcImage);
    namedWindow("Blue通道混合【效果图】");
    imshow("Blue通道混合【效果图】", srcImage);

    // Green 通道混合
    addWeighted(imageROIGreen, 1.0, logoImage, 0.5, 0.0, imageROIGreen);
    merge(channels, srcImage); // 将三个独立的独立的通道合并成一个三通道图像
    namedWindow("Green通道混合【效果图】");
    imshow("Green通道混合【效果图】", srcImage);

    // Red 通道混合
    addWeighted(imageROIRed, 1.0, logoImage, 0.5, 0.0, imageROIRed);
    merge(channels, srcImage);
    namedWindow("Red通道混合【效果图】");
    imshow("Red通道混合【效果图】", srcImage);

    return true;
}

int main (int argc, char *argv[]) {

    MultiChannelBlending();

    waitKey(0);

    return 0;
}
