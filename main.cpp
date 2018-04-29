#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【轮廓图】"

int main( int argc, char** argv )
{
    Mat image(600, 600, CV_8UC3);
    RNG &rng = theRNG();

    while (1) {
        // 参数初始化
        int cout = rng.uniform(3, 103);
        vector<Point> points;

        // 随机生成点坐标
        for (int i = 0; i < cout; ++i) {
            Point point;

            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
            points.push_back(point);
        }

        // 对给定的2D点集，寻找最小面积的包围矩形
        RotatedRect box = minAreaRect(Mat(points));
        Point2f vertex[4];
        box.points(vertex);

        // 绘制出随机颜色的点
        image = Scalar::all(0);
        for (int i = 0; i < cout; ++i) {
            circle(image,
                   points[i],
                   3,
                   Scalar(rng.uniform(0, 255),
                          rng.uniform(0, 255),
                          rng.uniform(0, 255)),
                   FILLED,
                   LINE_AA);
        }

        // 绘制最小面积的包围矩形
        for (int i = 0; i < 4; ++i) {
            line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
        }

        // 显示窗口
        imshow(WINDOW_NAME2, image);

        // 退出
        char key = (char)waitKey();
        if (27 == key || 'q' == key || 'Q' == key) {
            break;
        }
    }

    return 0;
}
