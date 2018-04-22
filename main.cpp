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
    Mat srcImage = imread ("../scharr.jpg");
    imshow("<0>【原图】", srcImage);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y, dst;

    // 求X方向梯度
    // 描述： Schaar()算子 边缘检测
    // 第一个参数： 原始输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 输出图像深度
    // 第四个参数： X方向差分阶数
    // 第五个参数： Y方向差分阶数
    // 第六个参数： 计算导数时可选的缩放因子
    // 第七个参数： 结果存入目标图之前可选的delta的值 默认值0
    // 第八个参数： 不用关心，需要用时需要修改参数
    Scharr(srcImage,
           grad_x,
           CV_16S,
           1,
           0,
           1,
           0,
           BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    // 求Y方向梯度
    Scharr(srcImage,
           grad_y,
           CV_16S,
           0,
           1,
           1,
           0,
           BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    // 合并梯度
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

    imshow("<1>【效果图】", dst);

    waitKey(0);

    return 0;
}
