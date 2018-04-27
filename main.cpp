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

vector<Mat> trainingImages; //用来存放训练图像信息的容器
vector<int> trainingLabels; //用来存放图像对应正负样本的值，正样本为1，负样本为0

int openfile(int flag, const char *dpath)
{//获取图像的路径
    vector<string> files;
    DIR *dir;
    struct dirent *ptr;
    if((dir = opendir(dpath)) == NULL)//打开文件夹
    {
        cout << __LINE__ << endl;
        return -1;
    }
    while((ptr = readdir(dir)) != NULL)
    {
        if(ptr->d_type > 4) //过滤. 和 ..
        {
            char name[30];
            char path[200];
            sprintf(path, "%s/%s", dpath, ptr->d_name); //将文件夹路径和图像名结合起来得到图像路径
            files.push_back(path);
            puts(path);
        }
    }
    closedir(dir);
    //将图像对应的值存放到容器中
    for (int i = 0; i < files.size(); i++)
    {
        Mat img = imread(files[i].c_str());
        Mat line_i = img.reshape(1, 1);

        trainingImages.push_back(line_i);
        trainingLabels.push_back(flag);
    }

    return 0;
}

int main()
{
    Mat classes;
    openfile(1, "/home/ws/tmp/opencv_learning/svm/posPlate/train");
    openfile(0, "/home/ws/tmp/opencv_learning/svm/negPlate/train");
    cout << __LINE__ << endl;
    Mat trainingData(trainingImages.size(), trainingImages[0].cols, CV_32FC1);
    for (int i = 0; i < trainingImages.size(); i++)
    {
        Mat temp(trainingImages[i]);
        temp.copyTo(trainingData.row(i));
    }
    trainingData.convertTo(trainingData, CV_32FC1);
    Mat(trainingLabels).copyTo(classes);
    classes.convertTo(classes, CV_32SC1);

    Ptr<SVM> model = SVM::create();//以下是设置SVM训练模型的配置
    model->setType(SVM::C_SVC);
    model->setKernel(SVM::LINEAR);
    model->setGamma(1);
    model->setC(1);
    model->setCoef0(0);
    model->setNu(0);
    model->setP(0);
    model->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER, 20000, 0.0001));


    Ptr<TrainData> tdata = TrainData::create(trainingData, ROW_SAMPLE, classes);
    //model->train(trainingData, ROW_SAMPLE, classes);
    model->train(tdata);
    model->save("car.xml");//保存

    return 0;
}
