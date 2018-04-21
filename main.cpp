#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 创建窗口 读取图像 显示图像
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../floodfill.jpg");
    imshow ("<0>【原图】", srcImage);

    // 创建窗口 水漫填充操作 显示效果图
    namedWindow("<1>水漫填充【效果图】");
    //描述：水漫填充操作，用我们指定的颜色从种子点开始填充一个连接域
    // 第一个参数： 需要水漫操作的图像，输入/输出1通道或3通道，8位或浮点图像，具体参数由之后的参数指明
    // 第二个参数： 操作掩膜
    // 第三个参数： 水漫填充算法的起点
    // 第四个参数： 像素点被渲染的值，即在重绘区域像素的新值
    // 第五个参数： 默认值0 用于设置floodFill函数将要重绘区域的最小边界举行矩形区域
    // 第六个参数： 默认值Scalar() 表示当前观察像素值与其部件邻域像素值或者待加入该部件的种子之间的亮度或颜色之负差的最大值
    // 第七个参数： 默认值Scalar() 表示当前观察像素值与其部件邻域像素值或者待加入该部件的种子之间的亮度或颜色之正差的最大值
    // 第八个参数： 操作标志符 低八位：控制算法的连通性
    // 重载函数的第一个函数
    floodFill(srcImage,
              Point(50, 300),
              Scalar(0, 0, 255), NULL,
              Scalar(20, 20, 20),
              Scalar(20, 20, 20),
              4);

    imshow("<1>水漫填充【效果图】", srcImage);

    waitKey(0);
    return 0;
}
