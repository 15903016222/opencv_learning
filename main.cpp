#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../houghLines.jpg");
    imshow("<0>【原图】", srcImage);

    namedWindow("<1>临时图片");
    namedWindow("<2>【效果图】");

    Mat tmpImage, dstImage;
    // 边缘检测
    // 滤波 边缘检测
    Canny(srcImage, tmpImage, 50, 200, 3);
    imshow("<1>临时图片", tmpImage);
    // 边缘检测的图转换为灰度图 需再次转换为彩色图
    cvtColor(tmpImage, dstImage, COLOR_GRAY2BGR);

    // 进行霍夫变换
    vector<Vec4i> lines;
    // 描述：标准霍夫变换
    // 第一个参数： 输入图像
    // 第二个参数： 用于存放霍夫变换检测到的线条输出矢量 每条线条有四个参数(x_1, y_1, x_2, y_2) 直线的两个点
    // 第三个参数： 以像素为单位的距离精度，
    // 第四个参数： 以弧度为单位的角度京精度
    // 第五个参数： 累加平面的阀值参数，即识别某一条直线时，他在累加平面中必须达到的值
    // 第六个参数： 默认值0 最低线段的长度， 比这个长度小的不显示出来
    // 第七个参数： 默认值0 允许同一行，点与点之间连接起来的最大距离
    HoughLinesP(tmpImage,
               lines,
               1,
               CV_PI / 180,
               200,
               50,
               10);

    size_t i;
    for (i = 0; i < lines.size(); ++i) {
        Vec4i l = lines[i];

        line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(55, 100, 195), 1, LINE_AA);
    }
    cout << "i = " << i << endl;

//    imshow("<1>临时图片", tmpImage);
    imshow("<2>【效果图】", dstImage);
    waitKey(0);

    return 0;
}
