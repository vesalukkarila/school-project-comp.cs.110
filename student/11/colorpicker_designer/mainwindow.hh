#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow   //oma luokka joka perii QMainWindow-luokan (QMainQindow - QWidget - QObject)
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:  //slotit jotka ovat luokan omaan käyttöön eli vain luokka itse voi sitoa signaaleja näihin
    void onColorChanged();  //miten ikkunan on tarkoitus toimia kun käyttäjä muuttaa värin arvoa

    void on_horizontalSliderRed_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    const int RGB_VALUE_MAX = 255;
    /*Luokan private-osassa on määriteltynä jäsenmuuttujat aivan kuten muillakin luokilla.
     * Kuten edellisellä ohjelmointikurssilla opimme, käyttöliittymäluokan jäsenmuuttujina voi olla sen sisältämiä
     * käyttöliittymäkomponentteja. Jäsenmuuttujiksi kannattaa tallettaa vain ne käyttöliittymäkomponentit,
     * joita meidän pitää pystyä käsittelemään ohjelmakoodissa. Tästä syystä luokalla ei ole yhtään widgettiä attribuuttinaan.
     * Tässä esimerkissä kaikki widgetit on määritelty Qt Designerin kautta, jota opit käyttämään seuraavassa harjoitusosiossa.
     * Ohjelmakoodissa näihin widgeteihin voidaan viitata käyttöliittymän (ui) kautta.
     * Luokkarajapinnassa on määriteltynä myös vakio RGB-arvojen maksimiarvolle.*/
};

#endif // MAINWINDOW_HH
