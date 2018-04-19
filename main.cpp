#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 缩减空间颜色的三种方法
void colorReduce1(Mat &inputImage, Mat & outputImage, int div);
void colorReduce2(Mat &inputImage, Mat & outputImage, int div);
void colorReduce3(Mat &inputImage, Mat & outputImage, int div);

int main (int argc, char *argv[]) {

    Mat srcImage = imread("../colorReduce.jpg", 1);
    imshow("原始图", srcImage);

    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

    double time0 = static_cast<double>(getTickCount());
//    colorReduce1(srcImage, dstImage, 32);
//    colorReduce2(srcImage, dstImage, 32);
    colorReduce3(srcImage, dstImage, 32);
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "此方法运行时间：" << time0 << endl;
    imshow("效果图", dstImage);

    waitKey(0);

    return 0;
}

// 方法一：用指针访问像素 C操作像素 颜色缩减 所用时间：0.012s
void colorReduce1(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();

    for (int i = 0; i < rowNumber; ++i) {
        uchar *data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; ++j) {
            /* 以下两种方式的处理方式效果相同 */
            // 处理数据方式1
            data[j] = data[j] / div * div + div / 2; // 这种处理速度稍微快一点
            // 处理数据方式2
            //*data++ = *data / div * div + div / 2; // 这个处理速度稍微慢10ms
        }
    }
}

// 方法二：使用迭代器访问像素 耗时0.03s
void colorReduce2(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

    for (; it != itend; ++it) {
        (*it)[0] = (*it)[0] / div * div + div / 2;
        (*it)[1] = (*it)[1] / div * div + div / 2;
        (*it)[3] = (*it)[3] / div * div + div / 2;
    }

}

// 方法三：动态地址访问 耗时0.042s
void colorReduce3(Mat &inputImage, Mat &outputImage, int div) {
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;

    for (int i = 0; i < rowNumber; ++i) {
        for (int j = 0; j < colNumber; ++j) {
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;
        }
    }

}
