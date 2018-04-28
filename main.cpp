#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <vector>
using namespace cv;
using namespace std;
using namespace ml;

int openfile(int flag, const char *dpath)
{//获取图像的路径
    DIR *dir;
    struct dirent *ptr;
    if((dir = opendir(dpath)) == NULL)//打开文件夹
    {
        cout << __LINE__ << endl;
        return -1;
    }
    int count = 0;
    while((ptr = readdir(dir)) != NULL)
    {
        if(ptr->d_type > 4) //过滤. 和 ..
        {
            char name[200];
            char path[200];
            sprintf(path, "%s/%s", dpath, ptr->d_name); //将文件夹路径和图像名结合起来得到图像路径
            sprintf(name, "%s/ws/%04d.jpg", dpath, count++);
            Mat srcImage = imread(path);
            if (36 == srcImage.rows) {
                if (136 == srcImage.cols) {
                    continue;
                }
            }
            printf ("%s \n", path);
            printf ("%s \n", name);
            Mat dstImage;
            resize(srcImage, dstImage, Size(136, 36));
            imwrite(name, dstImage);
            cout << __LINE__ << endl;
        }
    }
    closedir(dir);

    return 0;
}

int main()
{
    openfile(1, "/home/ws/tmp/opencv_learning/svm/posPlate/train/ws");
    openfile(0, "/home/ws/tmp/opencv_learning/svm/negPlate/train/ws");

    return 0;
}
