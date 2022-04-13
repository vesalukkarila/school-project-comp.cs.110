#include "mainwindow.hh"
#include "gameboard_gui.hh"
#include "numbertile_gui.hh"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>    //poisto??

#include <QGridLayout>
#include <QPushButton>
#include <utility>
#include <QDebug>
#include <QFont>    //tarpeellinen?
#include <QLineEdit>    //tarpeellinen??
#include <map>
#include <QString>




const Coords LEFT = {0, -1};    //Saako nämä olla täällä vai private osassa?
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), seed_(0), goal_(0)    //Pitäs korjata cpp::222 conditional jump uninitialised values
{
    ui->setupUi(this);

    //Deaktivoidaan toiminnan ohjaamiseksi painonappeja
    ui->resetPushButton->setDisabled(true),
    ui->startPushButton->setDisabled(true),
    ui->upPushButton->setDisabled(true),
    ui->downPushButton->setDisabled(true),
    ui->leftPushButton->setDisabled(true),
    ui->rightPushButton->setDisabled(true);

    widgetit_tietorakenteeseen_ja_ruudulle();

    ui->textBrowser->setText("Tervetuloa. Valitse siemenluku väliltä 1-99. "
                    "Tavoitteen on oltava jokin 2:n potenssi väliltä 8-8192. "
                    "Nämä valittuasi pääset pelaamaan. "
                    "Jos haluat aloittaa alusta, paina Reset. "
                    "Paina Lopeta lopettaaksesi peli.");
}


MainWindow::~MainWindow()
{
    if (GAMEBOARD_EXISTS ==true)
        delete board_;  //tuhotaan dynaamisesti luotu gameboard olio, jos se on olemassa
    delete ui;
}



//VALMIS
void MainWindow::widgetit_tietorakenteeseen_ja_ruudulle()
{

    for (int rivi_luku = 0;  rivi_luku < SIZE; ++rivi_luku )
    {
        vector<QPushButton*> rivi;
        for (int sarake = 0; sarake < SIZE; ++sarake)
        {
            QPushButton* osoitin = new QPushButton("", this);
            osoitin->setFixedWidth(ruudun_koko);
            osoitin->setStyleSheet("background-color: beige");   //Heti alusta tän värinnen, tarpeellinen??

            rivi.push_back(osoitin);
            osoitin->setDisabled(true);             //deaktivoidaan
            ui->gridLayout_2->addWidget(osoitin, rivi_luku, sarake);    //Piirretään gridille


        }
        pb_vektori.push_back(rivi);
    }
}

//OK
//Muuttaa pelilaudan tietorakenteen graafiseksi.
//Värjää apufunktion avulla ruudut luvun mukaan.
//Ei paluuarvoa, ei parametria.
void MainWindow::backend_tietorakenne_graafiseksi()
{
    // SIZE tulee gameboard.hh tiedostosta,
    // jolloin graafinen skaalautuu kun ruutujen määrä muutetaan backendissä.
    for ( int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            pair <int, int> koordinaatit (y, x);
            // get_value on tekijän lisäämä funktio gameboard.cpp:ssä
            int numbertilen_arvo = board_->get_value(koordinaatit);

            // Tyylittelyt
            QString vari = hae_laatikon_vari(numbertilen_arvo);
            pb_vektori.at(y).at(x)->setStyleSheet({"font: bold; color: black; "
                                                   "background-color: "+vari});

            QString arvo_tekstiksi = QString::number(numbertilen_arvo);
            if (arvo_tekstiksi == "0")
                arvo_tekstiksi = "";

            pb_vektori.at(y).at(x)->setText(arvo_tekstiksi);
        }
    }
}


//OK
// Palauttaa värin qstringinä, parametrina kokonaisluku.
QString MainWindow::hae_laatikon_vari(int luku)
{
    // Varmuuden vuoksi loopissa, jos luku puuttuisi mapista jonkin virheen vuoksi.
    for (auto tietopari : vari_kartta)
    {
        if (tietopari.first == luku)
            return tietopari.second;
    }
    return "beige";
}


//OK
// Asettaa seedspinboxin arvon attribuuttiin seed_
// Toiminnan ohjaamiseksi aktivoi/deaktivoi painonappeja.
void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seed_ = arg1;
    if (seed_ > 0 and is_goal_approved())
        ui->startPushButton->setEnabled(true);
    else
        ui->startPushButton->setDisabled(true);

}


//OK
// Asettaa goalspinboxin arvon attribuuttiin goal_
// Toiminnan ohjaamiseksi aktivoi/deaktivoi painonappeja.
void MainWindow::on_goalSpinBox_valueChanged(int arg1)
{
    goal_ = arg1;
    if (seed_ > 0 and is_goal_approved())
        ui->startPushButton->setEnabled(true);
    else
        ui->startPushButton->setDisabled(true);
}

//OK
// Aloittaa pelin.
// Toiminnan ohjaamiseksi aktivoi/deaktivoi painonappeja.
void MainWindow::on_startPushButton_clicked()
{
    ui->textBrowser->setText("Play hard!");
    //Luo backendissä tietorakenteen ja kaikki tarvittava aloitusta varten
    luo_backend_tai_palauttaa_alkutilanteeseen();

    //Looppaa widgetit ja kirjoittaa niihin numbertilen arvon
    backend_tietorakenne_graafiseksi();

    ui->resetPushButton->setEnabled(true);
    ui->startPushButton->setDisabled(true);
    ui->goalSpinBox->setDisabled(true);
    ui->seedSpinBox->setDisabled(true);
    ui->upPushButton->setEnabled(true);
    ui->downPushButton->setEnabled(true);
    ui->leftPushButton->setEnabled(true);
    ui->rightPushButton->setEnabled(true);
}

//OK
// Luo backend-tietorakenteen tai muokkaa sitä jos jo olemassa.
// Ei paluuarvoa, ei parametreja.
void MainWindow::luo_backend_tai_palauttaa_alkutilanteeseen()
{
    //GAMEBOARD-EXISTS gameboard_gui.hh:ssa näin sitä voidaan käyttää myös
    //gameboard_gui.cpp:n fill() funktiossa, jota muokattu.
    if (GAMEBOARD_EXISTS == false)
    {
        board_ = new GameBoard;
        board_->init_empty();
        board_->fill(seed_);
        GAMEBOARD_EXISTS = true;

    }

    else
    {
        board_->fill(seed_);
    }

}

// OK
// Keskeyttää pelin aktivoimalla/deaktivoimalla painonappeja.
// Nolla spinboxit, peliohje textbrowseriin.
void MainWindow::on_resetPushButton_clicked()
{
   ui->seedSpinBox->setValue(0);
   ui->goalSpinBox->setValue(0);
   ui->textBrowser->setText("Nyt voi aloittaa pelin alusta, tässä ohjeet: "
                    "Valitse siemenluku väliltä 1-99. "
                    "Tavoitteen on oltava jokin 2:n potenssi väliltä 8-8192. "
                    "Nämä valittuasi pääset pelaamaan");

   //Widgettien aktivointi ja deaktivointi toiminnan ohjaamiseksi, pakottaa Starttiin
   ui->seedSpinBox->setEnabled(true);
   ui->goalSpinBox->setEnabled(true);
   ui->resetPushButton->setDisabled(true);
   //Ja suunnat..
   ui->upPushButton->setDisabled(true);
   ui->downPushButton->setDisabled(true);
   ui->leftPushButton->setDisabled(true);
   ui->rightPushButton->setDisabled(true);

}

// OK
// Tarkistaa onko tavoiteluku kakkosen potenssi.
// Paluuarvona boolean, ei parametreja.
bool MainWindow::is_goal_approved()
{
    for (auto i : APPROVED_GOALS)
        if (goal_ == i)
            return true;
    return false;
}


// OK
// Välittää suuntakäskyn backendille ja lisää uuden ruudun.
// Tarkistaa voitto&häviötilanteen, piirtää muutokset graafiseksi.
void MainWindow::on_upPushButton_clicked()
{
    if (board_->move(UP, goal_))
    {
        voitto_funktio();
        return;
    }

    else if (board_->is_full())
    {
        havio_funktio();
        return;
    }

    board_->new_value(false);
    backend_tietorakenne_graafiseksi();
}

// OK
// Välittää suuntakäskyn backendille ja lisää uuden ruudun.
// Tarkistaa voitto&häviötilanteen, piirtää muutokset graafiseksi.
void MainWindow::on_rightPushButton_clicked()
{
    if (board_->move(RIGHT, goal_))
    {
        voitto_funktio();
        return;
    }

    else if (board_->is_full())
    {
        havio_funktio();
        return;
    }

    board_->new_value(false);
    backend_tietorakenne_graafiseksi();
}

// OK
// Välittää suuntakäskyn backendille ja lisää uuden ruudun.
// Tarkistaa voitto&häviötilanteen, piirtää muutokset graafiseksi.
void MainWindow::on_downPushButton_clicked()
{
    if (board_->move(DOWN, goal_))
    {
        voitto_funktio();
        return;
    }

    else if (board_->is_full())
    {
        havio_funktio();
        return;
    }

    board_->new_value(false);
    backend_tietorakenne_graafiseksi();
}

// OK
// Välittää suuntakäskyn backendille ja lisää uuden ruudun.
// Tarkistaa voitto&häviötilanteen, piirtää muutokset graafiseksi.
void MainWindow::on_leftPushButton_clicked()
{
    if (board_->move(LEFT, goal_))
    {
        voitto_funktio();
        return;
    }

    else if (board_->is_full())
    {
        havio_funktio();
        return;
    }

    board_->new_value(false);
    backend_tietorakenne_graafiseksi();
}

//OK
// Voittotilanteesta ilmoitus. Ohjaa painamaan Reset tai Lopeta painonappeja
// aktivoimalla/deaktivoimalla.
// Ei paluuarvoa, ei parametreja.
void MainWindow::voitto_funktio()
{
    QString tavoite = QString::number(goal_);
    ui->textBrowser->setText("Voitit! Saavutit tavoitteen " +tavoite +"."
                            " Paina Reset aloittaaksesi uudelleen tai "
                            "Sulje lopettaaksesi.");

    // Suuntien deaktivointi
    ui->upPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
}

// OK
// Häviötilanteesta ilmoitus. Ohjaa painamaan Reset tai Lopeta painonappeja
// aktivoimalla/deaktivoimalla.
// Ei paluuarvoa, ei parametreja.
void MainWindow::havio_funktio()
{
    ui->textBrowser->setText("Hävisit. Ruudukko on täynnä."
                            " Paina Reset aloittaaksesi uudelleen tai "
                            "Sulje lopettaaksesi");

    // Suuntanappien deaktivointi
    ui->upPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
}







