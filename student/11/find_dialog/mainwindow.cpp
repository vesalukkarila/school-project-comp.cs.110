#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <fstream>
#include <QFile> //for reading the text file
#include <QTextStream> //for converting the textfile to text stream
#include <QMessageBox> //for showing any message ifthe filepath is not corrrect or any other problems

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), testi_(), tiedosto_()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::on_keyLineEdit_textEdited(const QString &arg1)
{
    if (arg1 == "kala")
        testi_ = arg1;
}

*/
void MainWindow::on_keyLineEdit_textChanged(const QString &arg1)
{
    testi_ = arg1;
}



void MainWindow::on_findPushButton_clicked()
{
    QFile file(tiedosto_);
    if(!file.open(QIODevice::ReadOnly))
        ui->textBrowser->setText("File not found");
    else
    {
        ui->textBrowser->setText("Toimii"); //poista myhöemmin
        //avautuu mutta sanaa ei annettu
        if (testi_.size() == 0)
        {
            ui->textBrowser->setText("File found");
            file.close();
            return;
        }

        QTextStream stream(&file);      //voidrealm videosta, striimin määrittely
        {
            while(!stream.atEnd())
            {
                QString line = stream.readLine();
                //avautuu ja sana löytyy
                if (line.contains(testi_) and testi_.size() != 0)
                {
                    ui->textBrowser->setText("Word found");
                    file.close();
                    return;
                }
            }
            //avautuu mutta sanaa ei löydy
            ui->textBrowser->setText("Word not found");

        }
    }
    file.close();
}


void MainWindow::on_fileLineEdit_textChanged(const QString &arg1)
{
    tiedosto_ = arg1;
}

