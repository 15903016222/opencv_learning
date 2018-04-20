#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char *argv[]) {
    /* -------------写文件----------- */
    // 初始化
    FileStorage fs("../test.yaml", FileStorage::WRITE);

    // 开始写入文件
    fs << "frameCount" << 5;
    time_t rawtime;
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat camerMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "camerMatrix" << camerMatrix << "distCoeffs" << distCoeffs;
    fs << "features" << "[";
    for (int i = 0; i < 3; ++i) {
        int x = rand () % 640;
        int y = rand () % 480;
        uchar lbp = rand () % 256;

        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
        for (int j = 0; j < 8; ++j) {
            fs << ((lbp >> j) & 1);
        }
        fs << "]" << "}";
    }
    fs << "]";

    // 释放文件
    fs.release();

    /* -----------------读文件------------- */
    // 初始化
    FileStorage fs2("../test.yaml", FileStorage::READ);

    // 第一种方法读文件，对fileNode操作
    int frameCount = (int)fs2["frameCount"];
    cout << "frameCount : " << frameCount << endl;

    string data;
    // 第二种方法，使用FileNode >> 运算符
    fs2["calibrationDate"] >> data;
    cout << "clibrationDate : " << data;

    Mat camerMatrix2, distCoeffs2;
    fs2["camerMatrix"] >> camerMatrix2;
    fs2["distCoeffs"] >> distCoeffs2;

    // 打印信息
    cout << "frameCount:" << frameCount << endl
         << "calibration date:" << data << endl
         << "camera matrix:" << camerMatrix2 << endl
         << "distortion coeffs:" << distCoeffs2 << endl;

    // 第三种方法，使用FileNodeIterator遍历序列
    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    vector<uchar> lbpval;

    for (; it != it_end; ++it, ++idx) {
        cout << "feature #" << idx << ": ";
        cout << "x = " << (int)(*it)["x"]
             << ", y = " << (int)(*it)["y"]
             << ", lbp:(";
        (*it)["lbp"] >> lbpval;

        for (int i = 0; i < (int)lbpval.size(); ++i) {
            cout << " " << (int)lbpval[i];
        }
        cout << ")" << endl;
    }

    // 关闭文件
    fs2.release();

    waitKey(0);
    return 0;
}
