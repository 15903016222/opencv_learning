#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    // 以灰度的方式读取图像
    Mat srcImage = imread("../dft.jpg", 0);
    if (!srcImage.data) {
        cout << "读取图像失败" << endl;
        return -1;
    }
    imshow("原始图", srcImage);

    // 讲输入的图像扩展到最佳尺寸
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);

    // 为傅立叶变幻分配空间
    Mat padded;
    copyMakeBorder(srcImage,
                   padded,
                   0,
                   m - srcImage.rows,
                   0,
                   n - srcImage.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // 进行就地傅立叶变幻
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);

    // 将复数变换为幅值 M^2 = 实部^2 + 虚步^2
    split(complexI, planes);
    //        输入实部    输入虚部     输出幅度
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];

    // 进行对数尺寸的缩放 求自然对数 M1 = log(1 + M)
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage);

    // 剪切和重分布幅度象限
    // 若有奇数行 和 奇数列，进行频谱裁剪
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
    // 重新排列傅立叶图像中的象限，使得原点位于图像中心
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));

    // 交换象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q1);

    // 归一化 用0-1之间的浮点值将矩阵变幻为可视的图像格式
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    // 显示图片
    imshow("效果图",magnitudeImage);
    waitKey(0);

    return 0;
}
