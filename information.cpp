#include "information.h"

Information::Information(int encode, VideoCapture cap,QTimer* timer, QString filelocation,QString videolocation)
{
    this->encode = encode;
    this->cap = cap;
    this->filelocation = filelocation;
    this->videolocation = videolocation;
    this->timer = timer;
}

void Information::printinfo(){
    printf("encode: %d\nFile Location: %s\nVideo Location:%s\n",encode,filelocation.toStdString().c_str(),videolocation.toStdString().c_str());
    printf("");
}
