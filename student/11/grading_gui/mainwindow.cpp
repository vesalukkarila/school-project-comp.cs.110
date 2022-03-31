#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), n_(), g_(), p_(), e_()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    n_ = arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    g_ = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    p_ = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    e_ = arg1;
}


void MainWindow::on_countPushButton_clicked()
{
    unsigned int arvosana = count_final_grade(n_, g_, p_, e_);
    QString muutettu_stringiksi = QString::fromStdString(std::to_string(arvosana));
    ui->textBrowser->setText("Total grade: " + muutettu_stringiksi );
}

