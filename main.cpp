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
    namedWindow(WINDOW_NAME1);
    Mat image(600, 600, CV_8UC3);
    RNG rng = theRNG();

    while (1) {
        // 参数设置
        char key;
        int  count = (unsigned)rng % 100 + 3;
        vector<Point> points;

        for (int i = 0; i < count; ++i) {
            Point point;
            point.x = rng.uniform(image.cols / 4, image.rows * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
            points.push_back(point);
        }

        // 检测凸包
        vector<int> hull;
        // 描述：寻找凸包点
        // 第一个参数： 输入二维点集
        // 第二个参数： 输出参数，后面找到凸包
        // 第三个参数： 凸包的方向，为真时，顺时针方向，
        // 第四个参数： 操作标识符，默认值为true，为真时，返回凸包各点的指数
        convexHull(Mat(points),
                   hull,
                   true,
                   true);

        image = Scalar::all(0);
        for (int i = 0; i < count; ++i) {
            circle(image,
                   points[i],
                   3,
                   Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)),
                   FILLED,
                   LINE_AA);
        }

        // 准备绘制凸边的参数
        int hullcount = (int)hull.size();
        Point point0 = points[hull[hullcount - 1]];

        // 绘制凸边
        for (int i = 0; i < hullcount; ++i) {
            Point point = points[hull[i]];
            line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
            point0 = point;
        }
        cout << "hullcount: " << hullcount << endl;

        // 显示凸边
        imshow(WINDOW_NAME1, image);

        // 退出
        key = (char)waitKey();
        if (key == 27 || key == 'q' || key == 'Q') {
            break;
        }
    }

    waitKey(0);

    return 0;
}
