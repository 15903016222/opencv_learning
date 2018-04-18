#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("../show.jpg", 1);
    imshow("原图", srcImage);
    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_BGR2Lab);
    imshow("效果图", dstImage);
    waitKey(0);

    return 0;
}

