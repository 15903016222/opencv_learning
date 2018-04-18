#include <opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat image1, image2, image3;

    // 如果输入标志有冲突，则按较小的数字为准, 并且也会随着标志的不同
    // 图像的大小会减小
    //                            输入标志
    image1 = imread("../show.jpg", 2 | 4); // 载入无损图像
    imshow("Picture1", image1);

    image2 = imread("../show.jpg", 0); // 载入灰度图像
    imshow("Picture2", image2);

    image3 = imread("../show.jpg", 199); // 载入3通道的彩色图像, 图像减小为1/8
    imshow("Picture3", image3);

    waitKey(0);

    return 0;
}
