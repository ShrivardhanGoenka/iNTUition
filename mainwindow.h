#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videoinfo.h"
#include "videotab.h"
#include <QMainWindow>
#include <inputdialog.h>
#include <QMessageBox>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <thread>

using namespace std;
using namespace cv;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    VideoCapture cap;
    QTimer* timer;
     Ui::MainWindow *ui;
    vector<VideoTab*> vec;
    int test = 0;
    static void testthread(VideoTab*);

private slots:
    void on_pushButton_clicked();
    void tab_closed(int);
    void updatevideo();



private:

};
#endif // MAINWINDOW_H
