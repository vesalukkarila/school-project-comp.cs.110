#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

/*Rakentajan alustuslistassa alustetaan kaikki jäsenmuuttujina olevat käyttöliittymäkomponentit,
 * kuten olemme jäsenmuuttujille tottuneet tekemään.
 * Rakentajan rungossa tehdään käyttöliittymäkomponenteille vielä joitain asetuksia,
 * joita niiden rakentajassa ei suoraan voi tehdä (setMinimum ja setMaximum).
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSliderRed->setMinimum(0);
    ui->horizontalSliderRed->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreen->setMinimum(0);
    ui->horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlue->setMinimum(0);
    ui->horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxRed->setMinimum(0);
    ui->spinBoxRed->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxGreen->setMinimum(0);
    ui->spinBoxGreen->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxBlue->setMinimum(0);
    ui->spinBoxBlue->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &MainWindow::onColorChanged); //object1, signal1, object2, slot2
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
/*
   connect(ui->horizontalSliderRed, &QSlider::valueChanged, ui->spinBoxRed, &QSpinBox::setValue);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, ui->spinBoxGreen, &QSpinBox::setValue);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, ui->spinBoxBlue, &QSpinBox::setValue);
    connect(ui->spinBoxRed, &QSpinBox::setValue, ui->horizontalSliderRed, &QSlider::valueChanged);*///yritetty kirjoittaa suoraan

    onColorChanged();
}
/*Tärkeimpänä kohtana rakentajan rungon lopussa nähdään, miten jokaisen liukusäätimen muutossignaali yhdistetään
 * MainWindow-olion slotiin onColorChanged, jonka tarkoitus jo edellä mainittiinkin.
 * Harjoitustehtäväksi on jätetty liukusäätimien ja valintalaatikoiden muutossignaalien yhdistäminen toisiinsa pareittain.
 * Signaalien ja slotien lopullinen tilanne on esitetty edellisessä kuvassa. Vertaile koodia ja kuvaa toisiinsa ja yritä selvittää,
 * mitkä kytkennät on jo tehty ja mitkä on jätetty harjoitustehtäväksi.*/

MainWindow::~MainWindow()
{
    delete ui;  //tuhoaa attribuuttiosoittimen dynaamisen kohteen
}

/*Slotin onColorChanged toteutus on lyhyt. Siinä luodaan QColor-tyyppinen olio, jonka voi näyttää QLabel-oliossa.
 * Luotavan olion RGB-arvo, joka välitetään rakentajalle, saadaan haettua liukusäädinolioilta.*/
void MainWindow::onColorChanged()   //miten ikkunan on tarkoitus toimia kun käyttäjä muuttaa värin arvoa
{
    //qDebug() << "onColorChanged";
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());

    QPixmap colorMap(64, 64);
    colorMap.fill(selectedColor);
    ui->colorLabel->setPixmap(colorMap);
}




void MainWindow::on_horizontalSliderRed_valueChanged(int value)
{
    ui->spinBoxRed->setValue(value);
}


void MainWindow::on_spinBoxRed_valueChanged(int arg1)
{
    ui->horizontalSliderRed->setValue(arg1);
}


void MainWindow::on_spinBoxGreen_valueChanged(int arg1)
{
    ui->horizontalSliderGreen->setValue(arg1);
}



void MainWindow::on_horizontalSliderGreen_valueChanged(int value)
{
    ui->spinBoxGreen->setValue(value);
}


void MainWindow::on_horizontalSliderBlue_valueChanged(int value)
{
    ui->spinBoxBlue->setValue(value);
}


void MainWindow::on_spinBoxBlue_valueChanged(int arg1)
{
    ui->horizontalSliderBlue->setValue(arg1);
}

