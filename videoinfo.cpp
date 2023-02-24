#include "videoinfo.h"
#include "QtCore/qdebug.h"

VideoInfo::VideoInfo(int encode, VideoCapture cap,QTimer* timer, QString filelocation,QString videolocation,VideoTab* tab)
{
    this->encode = encode;
    this->cap = cap;
    this->filelocation = filelocation;
    this->videolocation = videolocation;
    this->timer = new QTimer(this);
    qDebug()<<videolocation;
    this->tab = tab;
    fps = cap.get(CAP_PROP_FPS);
    isrecording=0;
    cap>>frame;
    cvtColor(frame,frame,COLOR_BGR2RGB);
    framesize = new Size(static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)),static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)));
    play = 1;
}

void VideoInfo::inittimer(){
    timer->start(1000/fps);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updatecap()));
}

void VideoInfo::initrecorder(){
    isrecording = 1;
    //string temp = videolocation.QString::toStdString()+"test" + (recordingnumber++) + ".mp4";
    string newfile = (videolocation.QString::toStdString()+"test" + currentDateTime() + ".mp4");
    w = new VideoWriter(newfile,VideoWriter::fourcc('M', 'P', '4', 'V'),fps,*framesize,true);
}

void VideoInfo::stoprecording(){
    if(isrecording==1){
        w->release();
    }
}

void VideoInfo::updatecap(){
    if(play==0) return;
    cap.read(frame);
    if(isrecording){
        w->write(frame);
    }
    cvtColor(frame,frame,COLOR_BGR2RGB);

}

std::string VideoInfo::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
