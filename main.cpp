#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../warp.jpg");
    imshow("<0>【原图】", srcImage);

    // 参数准备
    Point2f srcTraingle[3];
    Point2f dstTraingle[3];

    Mat rotMat (2, 3, CV_32FC1);
    Mat warpMat (2, 3, CV_32FC1);
    Mat dstWarpImage, dstWarpRotateImage;

    dstWarpImage = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

    srcTraingle[0] = Point2f(0, 0);
    srcTraingle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
    srcTraingle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

    dstTraingle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0),
                             static_cast<float>(srcImage.rows * 0.33));
    dstTraingle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65),
                             static_cast<float>(srcImage.rows * 0.35));
    dstTraingle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15),
                             static_cast<float>(srcImage.rows * 0.6));

    // 求得放射变换矩阵
    warpMat = getAffineTransform(srcTraingle, dstTraingle);

    // 对原图像应用刚刚求得的放射映射
    // 描述： 对图像放射变换操作
    // 第一个参数： 输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 2X3矩阵
    // 第四个参数： 输出图像的尺寸
    // 第五个参数： 线性插值
    // 第六个参数： 边界模式
    warpAffine(srcImage,
               dstWarpImage,
               warpMat,
               dstWarpImage.size(),
               INTER_LINEAR,
               BORDER_CONSTANT);

    // 对图像进行缩放后再变换
    Point center = Point(dstWarpImage.cols / 2, dstWarpImage.rows / 2);
    double angle = -30.0;
    double scale = 0.8;

    // 获取变换矩阵
    rotMat = getRotationMatrix2D(center, angle, scale);
    // 对图像按照变换矩阵，进行放射映射变换操作
    warpAffine(dstWarpImage, dstWarpRotateImage, rotMat, dstWarpImage.size());

    imshow("<1>放射映射【效果图】", dstWarpImage);
    imshow("<2>图像变换【效果图】", dstWarpRotateImage);

    waitKey(0);

    return 0;
}
