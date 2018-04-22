#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void showHelpText () {
    printf( "\n\n\t按键操作说明: \n\n"
        "\t\t鼠标点击图中区域- 进行漫水填充操作\n"
        "\t\t键盘按键【ESC】- 退出程序\n"
        "\t\t键盘按键【q】  - 退出程序\n"
        "\t\t键盘按键【a】  - pyrUp   放大图像\n"
        "\t\t键盘按键【w】  - resize  放大图像\n"
        "\t\t键盘按键【s】  - pyrDown 缩小图像\n"
        "\t\t键盘按键【d】  - resize  缩小图像\n" );
}

int main( int argc, char** argv )
{
    // 创建窗口 读取图片 显示原图
    namedWindow("<0>【原图】");
    Mat srcImage = imread ("../pyr_resize.jpg");
    imshow("<0>【原图】", srcImage);

    showHelpText();

    // 创建窗口 图像调整后的矩阵 图像调整尺寸 显示效果图
    Mat tmpImage = srcImage;
    Mat dstImage = tmpImage;
    namedWindow("<1>【效果图】");

    int key = 0;

    while (1) {
        key = waitKey (30);
        switch (key) {
        case 27:
            return 0;
            break;
        case 'q':
            return 0;
            break;

        /* --------------图像放大------------ */
        case 'a':
            pyrUp(tmpImage,
                  dstImage,
                  Size(tmpImage.cols << 1, tmpImage.rows << 1),
                  BORDER_DEFAULT);
            break;
        case 'w':
            resize(tmpImage,
                   dstImage,
                   Size(tmpImage.cols << 1, tmpImage.rows << 1));
            break;

        /* -------------图像缩小------------- */
        case 'd':
            pyrDown(tmpImage,
                    dstImage,
                    Size(tmpImage.cols >> 1, tmpImage.rows >> 1),
                    BORDER_DEFAULT);
            break;
        case 's':
            resize(tmpImage,
                   dstImage,
                   Size(tmpImage.cols >> 1, tmpImage.rows >> 1));
            break;
        }

        imshow("<1>【效果图】", dstImage);
    }

    return 0;
}
