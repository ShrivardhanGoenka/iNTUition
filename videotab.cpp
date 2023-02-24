#include "videotab.h"
#include "QtCore/qtimer.h"
#include "ui_videotab.h"

VideoTab::VideoTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoTab)
{
    ui->setupUi(this);
}

VideoTab::~VideoTab()
{
    delete ui;
}

void VideoTab::updatevideo(Mat frame){
    QImage qt_image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->video->setPixmap(QPixmap::fromImage(qt_image).scaled(ui->video->width(), ui->video->height(), Qt::KeepAspectRatio));

}

void VideoTab::maininit(){
    fps = cap.get(CAP_PROP_FPS);
    isrecording=0;
    cap>>frame;
    cvtColor(frame,frame,COLOR_BGR2RGB);
    framesize = new Size(static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)),static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)));
    play = 1;
    ui->locationlabel->setText(videolocation);
}

void VideoTab::on_play_clicked()
{
    play = !play;
    if(play){
        ui->play->setText("Pause");
    }
    else
        ui->play->setText("Play");
}

void VideoTab::initrecorder(){
    isrecording = 1;
    //string temp = videolocation.QString::toStdString()+"test" + (recordingnumber++) + ".mp4";
    std::string newfile = (videolocation.QString::toStdString()+"test" + currentDateTime() + ".mp4");
    w = new VideoWriter(newfile,VideoWriter::fourcc('M', 'P', '4', 'V'),fps,*framesize,true);
}

void VideoTab::stoprecording(){
    if(isrecording==1){
        w->release();
    }
}

std::string VideoTab::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void VideoTab::on_pushButton_2_clicked()
{
    qDebug()<<"Reached here";
    QImage qt_image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    string file = videolocation.toStdString() + "Pic" + currentDateTime() + ".png";
    qDebug()<<QString::fromStdString(file);
    qt_image.save(QString::fromStdString(file));
}


void VideoTab::on_pushButton_clicked()
{
    if(isrecording){
        isrecording = 0;
        w->release();
        ui->pushButton->setText("Record");
    }
    else{
        isrecording = 1;
        string file = videolocation.toStdString() + "Video" + currentDateTime() + ".mp4";
        w = new VideoWriter(file,VideoWriter::fourcc('M', 'P', '4', 'V'),fps,*framesize,true);
        ui->pushButton->setText("Stop Recording");
    }
}


void VideoTab::on_Browse_clicked()
{
    videolocation = QFileDialog::getExistingDirectory(this,"",videolocation, QFileDialog::ShowDirsOnly);
    if(videolocation[videolocation.size()-1] != '/')
    videolocation += '/';
    ui->locationlabel->setText(videolocation);
    qDebug()<<videolocation;
}

