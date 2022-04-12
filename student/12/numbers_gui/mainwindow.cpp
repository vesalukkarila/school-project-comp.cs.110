#include "mainwindow.hh"
#include "gameboard_gui.hh"
#include "numbertile_gui.hh"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>    //poisto??

#include <QGridLayout>
#include <QPushButton>
#include <utility>


const Coords LEFT = {0, -1};
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

    init_empty_blocks();

    ui->textBrowser->setText("Tervetuloa pelaamaan, tässä ohjeet...:");

/*
    //Canvas jolle ruudut luodaan
    scene_ = new QGraphicsScene(this);  //grview vaatii grscenen joka asetetaan grviewhen
    int left_margin = 5;
    int top_margin = 5;

    ui->graphicsView->setGeometry(left_margin, top_margin, 300, 300);  //määritellään koodillisesti view:n sijainti&koko
    ui->graphicsView->setScene(scene_);             //scenen osoittama grscene view-widgetin sisään

    scene_->setSceneRect(left_margin, top_margin, 299, 299);   //299 vois muuttaa consteiks samoin yllää olevat 300:T

    scene_->setBackgroundBrush(Qt::green);
    */


//gridin yhdistmisen yritystä grviewiin
    /*
    QGridLayout* gLayout = new QGridLayout(this);
    grid_lay_out_ = gLayout;
    grid_lay_out_->
*/


    //Okei, piirto onnistuu, grview:ta ei ole koodillisesti käsitelty, ui:ssa vain laitettu esille

}

MainWindow::~MainWindow()
{
    if (GAMEBOARD_EXISTS ==true)
        delete board_;  //tuhotaan dynaamisesti luotu gameboard olio, jos se on olemassa
    delete ui;
}



//VALMIS
void MainWindow::init_empty_blocks()
{
    //vektorinvektorinalkioihin osoittimet widgetteihin jotka painonappeja tai labeleita tai rectangleja
    //asetellaan ne scenelle
    //myöhemmin backendistä niille luvut tekstinä startin painalluksesta ja nuolinäppäimet muuttaa backendiä ja taas loopaus läpi ja
    //tekstin muuttaminen

    //QWidget* central = new QWidget(this);       //PARAMETREJA SIJAINNISTA NÄILLE???
    //QGridLayout* gLayout = new QGridLayout();    //Kirjainten kohdalla asettelu tehty gridlayoutin avulla

    // Defining red brush and palette for letters
    QBrush brush(Qt::red);
    QPalette palette;
    palette.setBrush(QPalette::Button, brush);
    //ylläoleva suoraan typewriteristä

    for (int rivi_luku = 0;  rivi_luku < SIZE; ++rivi_luku )
    {
        vector<QPushButton*> rivi;
        for (int sarake = 0; sarake < SIZE; ++sarake)
        {
            QPushButton* osoitin = new QPushButton("", this);
            osoitin->setFixedWidth(ruudun_koko);
            osoitin->setPalette(palette);

            rivi.push_back(osoitin);
            osoitin->setDisabled(true);             //deaktivoidaan
            ui->gridLayout_2->addWidget(osoitin, rivi_luku, sarake);


        }
        pb_vektori.push_back(rivi);
    }
}

//Valmis
void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seed_ = arg1;
    if (seed_ > 0 and is_goal_approved())
        ui->startPushButton->setEnabled(true);
    else
        ui->startPushButton->setDisabled(true);

}


//Valmis
void MainWindow::on_goalSpinBox_valueChanged(int arg1)
{
    goal_ = arg1;
    if (seed_ > 0 and is_goal_approved())
        ui->startPushButton->setEnabled(true);
    else
        ui->startPushButton->setDisabled(true);

    //Vaihtoehtona toi spin-widget joka vois muuttaa lukua esim just tuon vektorin mukaan jossa vain hyväksyttävät arvot
    //Sit vaihtiksena myös vain validi goal antaa raksin ruutuun ja vapauttaa näppäimiä
}


//valmis
void MainWindow::on_startPushButton_clicked()
{


    ui->textBrowser->setText("Play hard!");
    //Luo backendissä tietorakenne ja kaikki tarvittava aloitusta varten
    luo_backend_tai_palauttaa_alkutilanteeseen();


    //Looppaa widgetit ja kirjoittaa niihin numbertilen arvon
    backend_tietorakenne_graafiseksi();

    //Toiminnan ohjaamiseksi painonappien aktivointi ja deaktivointi
    ui->resetPushButton->setEnabled(true);
    ui->startPushButton->setDisabled(true);
    ui->goalSpinBox->setDisabled(true);
    ui->seedSpinBox->setDisabled(true);
    //Ja suunnat
    ui->upPushButton->setEnabled(true);
    ui->downPushButton->setEnabled(true);
    ui->leftPushButton->setEnabled(true);
    ui->rightPushButton->setEnabled(true);
}

//Valmis
void MainWindow::luo_backend_tai_palauttaa_alkutilanteeseen()
{
    if (GAMEBOARD_EXISTS == false)  //Siirretty gameboard.hh:n, näin sitä voi käyttää fillissä
    {
        board_ = new GameBoard;        //luodaan gb-pelilautaolio oman attribuuttiosoittimen päähän, MUISTA DELETOIDA KUN DYNAAMINEN
        board_->init_empty();   //gb:n metodi, tarvitaan vain ekan kerran, eli jos gb-olio ei ole olemassa
        board_->fill(seed_);    //gb:n metodi tarvitaan modattuna resetin painon jälkeen
        GAMEBOARD_EXISTS = true;

    }

    else
    {
        board_->fill(seed_);
    }

}


//Valmis
void MainWindow::backend_tietorakenne_graafiseksi()
{

    for ( int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            pair <int, int> koordinaatit (y, x);
            int numbertilen_arvo = board_->get_value(koordinaatit);
            QString arvo_tekstiksi = QString::number(numbertilen_arvo);
            if (arvo_tekstiksi == "0")
                arvo_tekstiksi = "";
            pb_vektori.at(y).at(x)->setText(arvo_tekstiksi);

        }
    }
}



void MainWindow::on_resetPushButton_clicked() //Luennosta 47:00 gameboard_fill muokattava (if lause) tai tehtävä
                        //oma metodi resetille joka antaa tyhjät arvo ja pakottaa valitsemaan uudet siemenen ja goalin
{

   ui->seedSpinBox->setValue(0);
   ui->goalSpinBox->setValue(0);
   ui->textBrowser->setText("Nyt voi aloittaa pelin alusta, tässä ohjeet...:");

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


//VALMIS Tarkistaa onko tavoiteluku kakkosen potenssi
bool MainWindow::is_goal_approved()
{
    for (auto i : APPROVED_GOALS)
        if (goal_ == i)
            return true;
    return false;
}


//VALMIS, VIKANA SE ETTEI TAPAHDU MITÄÄN JOS SUUNTAAN EI VOI LIIKKUA, KAIKKIIN SUUNTIIN SAMA, MUT VIKA BACKENDISSÄ
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
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    backend_tietorakenne_graafiseksi();
}

//VALMIS
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
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    backend_tietorakenne_graafiseksi();
}

//VALMIS
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
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    backend_tietorakenne_graafiseksi();
}

//VALMIS
void MainWindow::on_leftPushButton_clicked()
{
    if (board_->move(LEFT, goal_))  //Suorittaa board.moven, jos palautuu truena voittofunktio
    {
        voitto_funktio();
        return;

    }
    else if (board_->is_full())
    {
        havio_funktio();
        return;
    }


    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    backend_tietorakenne_graafiseksi();

}

void MainWindow::voitto_funktio()
{
    QString tavoite = QString::number(goal_);
    ui->textBrowser->setText("You won! you reached the goal" +tavoite);
    //plus aktivoinnit&deaktivoinnit, mahdollisesti nollaus tästä tai resetistä
    //Ehkä pakotus resetiin deaktivoinneilla ja sieltä backendin alustus lähtötilanteeseen
    // Suuntien deaktivointi
    ui->upPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
}

void MainWindow::havio_funktio()
{
    ui->textBrowser->setText("You lost. Can't add a new tile.");
    // Suuntien deaktivointi
    ui->upPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->rightPushButton->setDisabled(true);
}





