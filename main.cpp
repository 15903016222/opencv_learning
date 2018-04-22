#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    // 创建窗口 读取图片 显示原图
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../laplacian.jpg");
    imshow("<0>【原图】", srcImage);

    Mat grayImage, dstImage, absImage;
    // 高斯滤波 消除噪声
    GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // 转换为灰度图
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    // 使用Laplacian变换
    // 描述：使用拉普拉斯操作进行边缘检测
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像的深度
    // 第四个参数： 用于计算二阶导数的滤波器的孔径尺寸大小，大小必须为正奇数，且必须大于1
    // 第五个参数： 计算拉普拉斯的时候可选的比例因子，默认值1
    // 第六个参数： 存入输出图像之前可选delta值，默认值0
    // 第七个参数： 一般不关心，需要使用时，查看你文档
    Laplacian(grayImage,
              dstImage,
              CV_16S,
              3,
              1,
              0,
              BORDER_DEFAULT);

    // 计算绝对值，并将其格式转换位8bit
    convertScaleAbs(dstImage, absImage);

    imshow("<1>【效果图】", absImage);

    waitKey(0);

    return 0;
}
