#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QMessageBox>
using namespace cv;

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();
        Ui::InputDialog *ui;
    void display();
    int encode=0;
    QString file="";
    QString location="/Users/shrivardhangoenka/Downloads/";
    QString url = "";
    QString TabName;
    VideoCapture cap;
private slots:
    void myAccept();

    void on_TabName_textChanged(const QString &arg1);

    void on_fileButton_clicked();

    void on_URLName_textChanged(const QString &arg1);

    void on_urlButton_clicked();

    void on_webcamButton_clicked();

    void on_browsefile_clicked();

    void on_Browselocatin_clicked();

private:

};

#endif // INPUTDIALOG_H
