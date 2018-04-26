#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../hist.jpg");

    Mat dstImage;
    // 转换为灰度图
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
    // 进行直方图均衡操作， 其操作图针对的是灰度方面的操作
    equalizeHist(srcImage, dstImage);

    imshow("<0>【原图】", srcImage);
    namedWindow("<1>【效果图】");

    imshow("<1>【效果图】", dstImage);

    waitKey(0);

    return 0;
}
