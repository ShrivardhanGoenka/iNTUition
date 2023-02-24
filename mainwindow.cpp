#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoinfo.h"
#include "videotab.h"
#include <chrono>
using namespace std::chrono;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MainTab->setTabsClosable(true);
    connect(ui->MainTab,SIGNAL(tabCloseRequested(int)),this,SLOT(tab_closed(int)));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatevideo()));
    timer->start(30);
}

MainWindow::~MainWindow()
{
    for(auto i:vec){
        if(i->isrecording){
            i->w->release();
        }
        i->cap.release();
    }
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QScopedPointer<InputDialog> a(new InputDialog(this));
    a->TabName = "Tab";
    a->display();

    if(a->encode==-1){
        return;
    }
    if(a->encode==0)
        cap.open(0);
    else if(a->encode >=1)
        cap.open(a->file.QString::toStdString());
    VideoTab* tab = new VideoTab();
    tab->encode= a->encode;
    tab->cap = cap;
    tab->filelocation = a->file;
    tab->videolocation = a->location;
    tab->maininit();
    vec.push_back(tab);
    ui->MainTab->addTab(tab,a->TabName);
}

void MainWindow::tab_closed(int index)
{
    if(!(QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No)))
        return;
    QWidget* item = ui->MainTab->widget(index);
    vec[index]->cap.release();
    if(vec[index]->isrecording)
        vec[index]->w->release();
    vec.erase(vec.begin()+index);
    ui->MainTab->removeTab(index);
    delete(item);
}

void MainWindow::updatevideo(){
    auto start=high_resolution_clock::now();;
    int size = vec.size();
    vector<std::thread*> testvector;
    for(auto i:vec){
          testvector.push_back(new std::thread(testthread,i));
//        if(i->play){
//            try{
//                auto start1 = high_resolution_clock::now();

//                i->cap>>i->frame;
//                if(i->isrecording){
//                    i->w->write(i->frame);
//                }
//                cvtColor(i->frame,i->frame,COLOR_BGR2RGB);
//            }
//            catch(...){}
//        }
    }
    for(auto i:testvector){
        i->join();
    }

    int index = ui->MainTab->currentIndex();
    if(index==-1) return;
    vec[index]->updatevideo(vec[index]->frame);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    test++;
//    if(test%100 == 0)
//        qDebug()<<duration.count();
}

void MainWindow::testthread(VideoTab* i){
    if(i->play){
        try{
            auto start1 = high_resolution_clock::now();

            i->cap>>i->frame;
            if(i->isrecording){
                i->w->write(i->frame);
            }
            cvtColor(i->frame,i->frame,COLOR_BGR2RGB);
        }
        catch(...){}
    }
}
