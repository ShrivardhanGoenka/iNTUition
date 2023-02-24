#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include "videotab.h"
#include <QObject>
#include <QString>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QTimer>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

class VideoInfo: public QObject
{
    Q_OBJECT
public:
    VideoInfo(int, VideoCapture, QTimer*,QString,QString,VideoTab*);
    int encode;
    VideoCapture cap;
    VideoWriter* w;
    QTimer *timer;
    QString filelocation;
    QString videolocation;
    void printinfo();
    Mat frame;
    void inittimer();
    int isrecording;
    void initrecorder();
    float fps;
    Size* framesize;
    void stoprecording();
    int recordingnumber;
    int play;
    std::string currentDateTime();
    VideoTab* tab;

public slots:
    void updatecap();

};

#endif // VIDEOINFO_H
