#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// --------------[ROI_AddImage()函数]--------
// 函数名：ROI_AddIMage()
//   描述：利用感兴趣区域ROI实现图像叠加
// ------------------------------------------
bool ROI_addImage() {
    // 读入两个图像
    Mat srcImage = imread ("../dota_pa.jpg");
    Mat logoImage = imread ("../dota_logo.jpg");

    if (! srcImage.data) {
        cout << "读取srcImage错误" << endl;
        return false;
    }
    if (! logoImage.data) {
        cout << "读取logoImage错误" << endl;
        return false;
    }

    // 定义感兴趣ROI区域
    Mat imageROI = srcImage(Rect(200, 250, logoImage.rows, logoImage.cols));
    // 加载掩饰(必须是灰度)
    Mat mask = imread("../dota_logo.jpg", 0);

    logoImage.copyTo(imageROI, mask);

    namedWindow("利用ROI实现图像的叠加示例窗口");
    imshow("利用ROI实现图像的叠加示例窗口", srcImage);

    return true;
}

// -------------[LinearBlending()函数]----------
// 函数名：LinearBlending()
// 描述：利用addWeighted()函数实现线性混合
// ---------------------------------------------
bool linearBlending() {
    double alphaValue = 0.5;
    double betaValue = 1.0 - alphaValue;

    Mat srcImage2, srcImage3, dstImage;

    srcImage2 = imread ("../mogu.jpg");
    srcImage3 = imread ("../rain.jpg");

    if (! srcImage2.data) {
        cout << "读取srcImage2错误" << endl;
        return false;
    }
    if (! srcImage3.data) {
        cout << "读取srcImage3错误" << endl;
        return false;
    }

    // 权重加载函数详解,函数
    // dst = src1[I] * alpha + src2[I] * beta + gamma; I:表示多维数组的索引值
    // 第1个参数：需要加权的第一个数组
    // 第2个参数：第一个数组的权重
    // 第3个参数：需要加权的第二个数组
    // 第4个参数：第二个数组的权重
    // 第5个参数：需要加权的总和上的标量值
    // 第6个参数：需要输出的数组
    // 第7个参数：默认值-1，即等同于src1.depth()，表示两个图像的大小，深度相同
    addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

    namedWindow("线性混合【原图】");
    imshow("线性混合【原图】", srcImage2);

    namedWindow("线性混合【效果图】");
    imshow("线性混合【效果图】", dstImage);

    return true;
}

int main (int argc, char *argv[]) {

    ROI_addImage();

    linearBlending();

    waitKey(0);

    return 0;
}
