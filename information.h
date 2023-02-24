#ifndef INFORMATION_H
#define INFORMATION_H

#include <QString>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QTimer>
using namespace cv;
using namespace std;

class Information
{
public:
    Information(int, VideoCapture, QTimer*,QString,QString);
    int encode;
    VideoCapture cap;
    QTimer *timer;
    QString filelocation = "";
    QString videolocation = "";
    void printinfo();
};

#endif // INFORMATION_H
