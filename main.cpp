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

    return 0;
}

