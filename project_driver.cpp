#include "project_driver.h"
#include "./ui_project_driver.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
//#include <QQmlContext>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QMessageBox>
using namespace std;
double vin1=0;
double vout1=0;
double duty=0;
double iomax1=-1;
double hiomax=77.0;
double liomax=0;
double iripple=0.0;
double swf=0;
int swmul=1000;
int mul=1000;
project_driver::project_driver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::project_driver)
{
    ui->setupUi(this);
}

project_driver::~project_driver()
{
    delete ui;
}


void project_driver::on_pushButton_clicked()
{
    vin1=ui->vin->text().toDouble();
    vout1=ui->vout->text().toDouble();
    duty=vout1/vin1;
    QString dutyst = QString::number(duty);
    ui->lcdNumber->display(duty);
    ui->duty->setText(dutyst);
}


void project_driver::on_swfm_currentIndexChanged(int index)
{
    swf=ui->swf->text().toDouble();
    if(index==0)
    {
        swmul=1000*swf;
        mul=1000;
        ui->swf_2->setText(QString::number(swmul));
    }
    if(index==1)
    {
        swmul=1000000*swf;
        mul=1000000;
        ui->swf_2->setText(QString::number(swmul));
    }
    if(index==-1)
    {
        swmul=1000*swf;
        ui->swf_2->setText(QString::number(swmul));
    }
}


void project_driver::on_irpsugg_clicked()
{
    iomax1=ui->iomax->text().toDouble();

    liomax=0.2*iomax1*1000000;
    hiomax=0.4*iomax1*1000000;
    ui->ilrippslider->setSingleStep(10000);
    ui->ilrippslider->setMinimum((int)liomax);
    ui->ilrippslider->setMaximum((int)hiomax);


}


void project_driver::on_ilrippslider_sliderMoved(int position)
{
    iripple=(double)position/1000000.0;
    ui->iripp->setText(QString::number(iripple));
}


void project_driver::on_swf_valueChanged(double arg1)
{

    ui->swf_2->setText(QString::number(mul*arg1));

}

