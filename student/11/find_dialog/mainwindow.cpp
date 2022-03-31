#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <fstream>
#include <QFile> //for reading the text file
#include <QTextStream> //for converting the textfile to text stream
#include <QMessageBox> //for showing any message ifthe filepath is not corrrect or any other problems

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), nimi_(), tiedosto_()
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
    nimi_ = arg1;
}



void MainWindow::on_findPushButton_clicked()
{
    QFile file(tiedosto_);
    if(!file.open(QIODevice::ReadOnly))
        ui->textBrowser->setText("File not found");
    else
    {
        //avautuu mutta sanaa ei annettu
        if (nimi_.size() == 0)
        {
            ui->textBrowser->setText("File found");
            file.close();   //??tarpeellinen tässä??
            return;
        }
        bool found = false;


        QTextStream stream(&file);      //voidrealm videosta, striimin määrittely
        {
            while(!stream.atEnd())
            {
                QString apu = "";
                QString attriibuutinapu = "";
                QString line = stream.readLine();
                //avautuu ja sana löytyy
                if (line.contains(nimi_) and ui->matchCheckBox->isChecked())  //isoilla väliä ja löytyy
                {
                    ui->textBrowser->setText("Word found");
                    found = true;

                }
                else if (! ui->matchCheckBox->isChecked())    //jos isoilla kirjaimilla ei ole väliä
                {
                    for (auto c : line)
                    {
                        apu += c.toUpper();
                    }
                    for (auto k : nimi_)
                        attriibuutinapu += k.toUpper();
                    if (apu==attriibuutinapu)
                    {
                        ui->textBrowser->setText("Word found");
                        found = true;
                    }

                }
            }
            //avautuu mutta sanaa ei löydy
            if (found == false)
                ui->textBrowser->setText("Word not found");

        }
    }
    file.close();
}


void MainWindow::on_fileLineEdit_textChanged(const QString &arg1)
{
    tiedosto_ = arg1;
}

