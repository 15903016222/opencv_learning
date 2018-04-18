#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "显示创建Mat的七种方法：" << endl;

    cout << "方法一：" << endl;
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl;

    cout << "方法二：" << endl;
    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC(3), Scalar::all(0)); // 创建超过二维的矩阵

    cout << "方法三：" << endl;
    M.create(4, 4, CV_8UC(2));
    cout << "M = " << endl << " " << M << endl;

    cout << "方法四：采用Matble的方式创建" << endl;
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl;

    Mat O = Mat::ones(4, 4, CV_64F);
    cout << "O = " << endl << " " << O << endl;

    Mat Z = Mat::zeros(4, 4, CV_64F);
    cout << "Z = " << endl << " " << Z << endl;

    cout << "方法六：" << endl;
    Mat C = (Mat_<double> (3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl;

    cout << "方法七：" << endl;
    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl;

    cout << "格式化输出方法：" << endl;
    Mat r = Mat(10, 3, CV_8UC3);
    randn(r, Scalar::all(0), Scalar::all(255)); // 随机产生值填充矩阵, 下限(最小值)，上限(最大值)

    cout << "OpenCV[默认风格] = " << r << ";" << endl << endl;
    cout << "OpenCV[Python风格] = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "OpenCV[逗号分隔风格] = " << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    cout << "OpenCV[NUMPY风格] = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    cout << "OpenCV[C语言风格] = " << format(r, Formatter::FMT_C) << ";" << endl << endl;

    cout << "其它数据结构的输出格式:" << endl;
    Point2f p(6, 2);
    cout << "[二维点]p = " << p << ";\n" << endl;

    Point3f p3f(8, 2, 0);
    cout << "[三维点]p3f = " << p3f << ";\n" << endl;

    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    cout << "[基于Mat的vector]v = " << Mat(v) << endl;

    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = Point2f((float)(i * 5), (float)(i % 7));
    }
    cout << "[二位点向量]points = " << points << endl;

    return 0;
}

