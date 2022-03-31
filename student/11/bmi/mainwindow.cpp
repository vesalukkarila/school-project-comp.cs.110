#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include<algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    paino_string = ui->weightLineEdit->text();
    paino = paino_string.toDouble();
}


void MainWindow::on_heightLineEdit_editingFinished()
{
    pituus_string = ui->heightLineEdit->text();
    pituus = pituus_string.toDouble();
    pituus /= 100;

}


void MainWindow::on_countButton_clicked()
{
    if (paino <= 0 or paino_string.length() == 0)
    {
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->setText("");

    }
    else
    {
        indeksi = (paino/(pow(pituus, 2)));
        indeksi_string.setNum(indeksi);
        ui->resultLabel->setText(indeksi_string);
        if(indeksi < 18.5)
            ui->infoTextBrowser->setText("You are underweight.");
        else if (indeksi > 25)
            ui->infoTextBrowser->setText("You are overweight.");
        else
            ui->infoTextBrowser->setText("Your weight is normal.");


    }

}

