#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    connect(this,SIGNAL(accepted()),this,SLOT(myAccept()));
    disconnect(this,SIGNAL(accepted()),this,SLOT(accept()));
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::display(){
    encode= 0;
    ui->URLName->setDisabled(true);
    ui->TabName->setText(TabName);
    ui->location->setText(location);
    ui->fileLabel->setText(file);
    //ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    ui->webcamButton->setChecked(true);
    int r = this->exec();
    TabName = ui->TabName->text();


    if(r==0){
        encode = -1;
        return;
    }
    VideoCapture cap;
    if(encode==0){
        this->cap.open(0);
    }
    else if(encode ==1){
        this->cap.open(file.toStdString());
    }
    else{
        bool a = cap.open(ui->URLName->text().toStdString());
        file = ui->URLName->text();
        if(a) this->cap = cap;
        if(!a){
            QMessageBox message;
            message.critical(0,"Error","Please enter a valid URL to stream from!");
            ui->urlButton->setChecked(true);
            display();
            return;
        }
    }

}

void InputDialog::myAccept(){
    qDebug()<<"Accepted";

}


void InputDialog::on_TabName_textChanged(const QString &arg1)
{
    if(arg1=="")
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}


void InputDialog::on_fileButton_clicked()
{
    ui->URLName->setDisabled(true);
    encode = 1;
    if(file=="") ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    else ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}


void InputDialog::on_URLName_textChanged(const QString &arg1)
{
    if(arg1=="")
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}

void InputDialog::on_urlButton_clicked()
{
//    ui->FileName->setEnabled(false);
    encode = 2;
    ui->URLName->setDisabled(false);
    if(ui->URLName->text() == "")
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}


void InputDialog::on_webcamButton_clicked()
{
//    ui->FileName->setEnabled(false);
    encode = 0;
    ui->URLName->setDisabled(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}


void InputDialog::on_browsefile_clicked()
{
    file = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.mp4*)");
    ui->fileLabel->setText(file);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}

void InputDialog::on_Browselocatin_clicked()
{
    location = QFileDialog::getExistingDirectory(this,"",location, QFileDialog::ShowDirsOnly);
    ui->location->setText(location);
}

