#ifndef VIDEOTAB_H
#define VIDEOTAB_H

#include <QFileDialog>
#include <QWidget>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
using namespace std;
using namespace cv;

namespace Ui {
class VideoTab;
}

class VideoTab : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTab(QWidget *parent = nullptr);
    ~VideoTab();
    void updatevideo(Mat);
    Ui::VideoTab *ui;
    int encode;
    VideoCapture cap;
    VideoWriter* w;
    QString filelocation;
    QString videolocation;
    void printinfo();
    Mat frame;
    int isrecording;
    void initrecorder();
    float fps;
    Size* framesize;
    void stoprecording();
    int recordingnumber;
    int play;
    void maininit();
    std::string currentDateTime();

private slots:
    void on_play_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_Browse_clicked();

private:

};

#endif // VIDEOTAB_H
