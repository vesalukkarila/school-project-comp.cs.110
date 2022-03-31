#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(parent); //jäi epäselväksi, luodaan osoittimen päähän olio kirjastosta vissiin
    connect(timer, &QTimer::timeout, this, &MainWindow::updateLcd); //yhdistetään olioita ymmärtäisin

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetTimer);

    ui->lcdNumberMin->setStyleSheet("background-color: darkblue ");
    ui->lcdNumberSec->setStyleSheet("background-color: orange ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    timer->start(1000);
    time = 0;
}

void MainWindow::stopTimer()
{
    timer->stop();

}

void MainWindow::resetTimer()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    startTimer();
}
/*
void MainWindow::on_startButton_clicked()
{
    //if (ui->lcdNumberMin == 0 and ui->lcdNumberSec == 0)
    {
        timer->start(1000);
        time = 0;   //??
    }
    }


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    on_startButton_clicked();
}
*/
void MainWindow::updateLcd()
{
    time++;
    ui->lcdNumberMin->display(time/60);
    ui->lcdNumberSec->display(time&60);
}

