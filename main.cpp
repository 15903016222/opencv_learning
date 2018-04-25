#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    namedWindow("<1>【效果图】");
    Mat srcImage = imread ("../remap.jpg");
    imshow("<0>【原图】", srcImage);

    Mat dstImage;
    Mat map_x, map_y;
    dstImage.create(srcImage.size(), srcImage.type());
    map_x.create(srcImage.size(), CV_32FC1);
    map_y.create(srcImage.size(), CV_32FC1);

    cout << "CV_32FC1 = " << CV_32FC1 << endl
         << "type = " << srcImage.type() << endl
         << "size = " << srcImage.size() << endl;

    for (int j = 0; j < srcImage.rows; ++j) {
        for (int i = 0; i < srcImage.cols; ++i) {
            map_x.at<float>(j, i) = static_cast<float>(i);
            map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
        }
    }
    // 描述： 根据映射的方式，将图像进行重映射几何变换
    // 第一个参数： 输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 表示点(x, y)的一个映射
    // 第四个参数： 与上一个相同
    // 第五个参数： 插值方式 INTER_LINEAR双线型插值
    // 第六个参数： 边界模式
    // 第七个参数： 使用默认值Scalar(0, 0, 0)
    remap(srcImage,
          dstImage,
          map_x,
          map_y,
          CV_INTER_LINEAR,
          BORDER_CONSTANT,
          Scalar(0, 0, 0));

    imshow("<1>【效果图】", dstImage);

    waitKey(0);

    return 0;
}
