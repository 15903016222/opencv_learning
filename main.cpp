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
    Mat srcImage = imread ("../Canny.jpg");
    imshow("<0>【原图】", srcImage);

    // 高阶Canny()用法，转成灰度图，降噪，用canny，最后将得到的边缘最为掩码
    // 拷贝原图的效果上，得到彩色的边缘图
    Mat srcImage1 = srcImage.clone();

    Mat dstImage, edgeImage, grayImage;
    // 创建与src同类型和大小的矩阵【dstImage】
    dstImage.create(srcImage1.size(), srcImage1.type());
    // 将原图像转换为灰度图
    cvtColor(srcImage1, grayImage, COLOR_BGR2GRAY);
    // 均值滤波3x3内核滤波
    blur(grayImage, edgeImage, Size(3, 3));
    // 运行Canny算子
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 第一个滞后阀值
    // 第四个参数： 第二个滞后阀值
    // 第五个参数： 应用Sobel算子的孔径大小 默认值3
    // 第六个参数： 图像梯度幅度的标识 默认值false
    Canny(edgeImage, edgeImage, 3, 9, 3);
    // 将dstImage内的所有元素设置为0
    dstImage = Scalar::all(0);
    // 将获得的掩码，来将原图拷贝到输出图像
    srcImage1.copyTo(dstImage, edgeImage);

    imshow("<1>【效果图】", dstImage);
    imshow("<2>【掩码图】", edgeImage);

    waitKey(0);

    return 0;
}
