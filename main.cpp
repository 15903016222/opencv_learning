#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;
int g_ndirection = 0;

void on_Remap (int , void *) {

    for (int j = 0; j < g_srcImage.rows; ++j) {
        for (int i = 0; i < g_srcImage.cols; ++i) {
            switch (g_ndirection) {
            case 0:
                // 原图 必须是float型，因为rows和cols的数量会超过255,
                // 因为这个g_map_x, g_map_y只表示坐标位置信息
                g_map_x.at<float>(j, i) = static_cast<float>(i);
                g_map_y.at<float>(j, i) = static_cast<float>(j);
                break;
            case 1:
                // 上下颠倒
                g_map_x.at<float>(j, i) = static_cast<float>(i);
                g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
                break;
            case 2:
                // 左右颠倒
                g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
                g_map_y.at<float>(j, i) = static_cast<float>(j);
                break;
            case 3:
                // 上下 左右颠倒
                g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
                g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
                break;
            }

        }
    }

    // 描述： 根据映射的方式，将图像进行重映射几何变换
    // 第一个参数： 输入图像
    // 第二个参数： 输出图像
    // 第三个参数： 表示点(x, y)的一个映射
    // 第四个参数： 与上一个相同
    // 第五个参数： 插值方式 INTER_LINEAR双线型插值
    // 第六个参数： 边界模式
    // 第七个参数： 使用默认值Scalar(0, 0, 0)
    remap(g_srcImage,
          g_dstImage,
          g_map_x,
          g_map_y,
          CV_INTER_LINEAR,
          BORDER_CONSTANT,
          Scalar(0, 0, 0));

    imshow("<1>【效果图】", g_dstImage);
}

int main( int argc, char** argv )
{
    namedWindow("<0>【原图】");
    namedWindow("<1>【效果图】");
    g_srcImage = imread ("../remap.jpg");
    imshow("<0>【原图】", g_srcImage);

    g_dstImage.create(g_srcImage.size(), g_srcImage.type());
    g_map_x.create(g_srcImage.size(), CV_32FC1);
    g_map_y.create(g_srcImage.size(), CV_32FC1);

    createTrackbar("方向", "<1>【效果图】", &g_ndirection, 3, on_Remap, 0);

    on_Remap(g_ndirection, NULL);

    cout << "CV_32FC1 = " << CV_32FC1 << endl
         << "type = " << g_srcImage.type() << endl
         << "size = " << g_srcImage.size() << endl
         << "channel = " << g_srcImage.channels() << endl
         << "map.channels = " << g_map_x.channels() << endl;

    waitKey(0);

    return 0;
}
