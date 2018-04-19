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

int main (int argc, char *argv[]) {

    ROI_addImage();

    waitKey(0);

    return 0;
}
