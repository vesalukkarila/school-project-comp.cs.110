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
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
    init_empty_blocks();


    ui->textBrowser->setText("Tervetuloa pelaamaan, tässä ohjeet...:");
}

MainWindow::~MainWindow()
{
    delete board_;  //tuhotaan dynaamisesti luotu gameboard olio
    delete ui;
}

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
        vector<QPushButton*> rivi;  //VOIS muuttaa labeliks, tai sit deaktivoi buttonin
        for (int sarake = 0; sarake < SIZE; ++sarake)
        {
            QPushButton* osoitin = new QPushButton("", this);
            osoitin->setFixedWidth(ruudun_koko);
            osoitin->setPalette(palette);

            rivi.push_back(osoitin);
            ui->gridLayout_2->addWidget(osoitin, rivi_luku, sarake);


        }
        pb_vektori.push_back(rivi);
    }
/*Peliruudukon voi toteuttaa esimerkiksi QGraphicsScene-ominaisuutena sekä etiketteinä (label).
 * QGraphicsScene-ominaisuutta on käytetty liikkuvassa ympyrässä ja vesipisarapelissä, joten niistä voit katsoa mallia.

 *QGraphicsScene:lle voidaan asettaa erilaisia kuvioita kuten suorakulmioita tai ympyröitä.
 *Liikkuvan ympyrän esimerkissä sille asetettiin ympyrä, mutta tässä tarvitset suorakulmioita (QGraphicsRectItem).
 *Huomaa, että suorakulmioon ei voi asettaa tekstiä (lukuja), joten todennäköisesti tarvitset myös etikettejä (QLabel).*/



//Ihan eka tuo tietorakenne graafiseksi, graphicviewistä oli maininta ja saiko tehdä pelkästään labelilla, luennolta ohje?
//ALUSSA ILMAN ETTÄ MITÄÄN KLIKATAAN PITÄS SAADA RUUDUKKO (JA TEXTBROWSERIIN OHJEISTUSTEKSTI)

}




void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seed_ = arg1;
}



void MainWindow::on_goalSpinBox_valueChanged(int arg1)
{
    goal_ = arg1;
    //periaatteessa tässä vois tarkistaa onko goal hyväksyttävä ja sit updatestartbutton, movingcircle esimerkkinä
    /*Tavoiteluvun on tarkoitus olla kakkosen potenssi, joten tavoiteluvun kysymisen sijaan voit kysyä vastaavaa
     * potenssia (jolloin mahdollisia arvoja on huomattavasti vähemmän).*/

    //vois eka tarkistaa vaikka vektoria vasten että luku hyväksyttävä
    //Vaihtoehtona toi spin-widget joka vois muuttaa lukua esim just tuon vektorin mukaan jossa vain hyväksyttävät arvot
    //Sit vaihtiksena myös vain validi goal antaa raksin ruutuun ja vapauttaa näppäimiä
}



void MainWindow::on_startPushButton_clicked()
{

    if (seed_ > 0 and is_goal_approved())
    {
        ui->textBrowser->setText("Jepulis");
        //Luo backendissä tietorakenne ja kaikki tarvittava aloitusta varten
        initiate_gameboard();   //käy luomassa pelilautaolion ja alustaa sen alkua varten

        //Haluan loopata läpi widgetit ja kirjoittaa niihin numbertilen arvon
        tietorakenne_graafiseksi();




        //Mitä jos kävis tuon tietorakenteen läpi ja loisi labelit esim canvasille sen pohjalta suoraan
        //ja kun nuolinäppäimiä painetaan vie käskyn backendiin ja piirtää tietorakenteen uudelleen.., silloin
        //widgettejä piirretään koko ajan uusiksi
        //parempi tapa olisi varmaan muuttaa widgettien arvoa tietorakenteen pohjalta 0-2048 väliltä

    }
    else
        ui->textBrowser->setText("Siemenluvun täytyy olla suurempi kuin nolla ja tavoiteluvun "
                                        "jokin 2:n potenssi, kuitenkin maksimissaan 8192.");
}


void MainWindow::initiate_gameboard()
{
    if (GAMEBOARD_EXISTS == false)  //siltä varalta että reset yhteydessä haluaa käyttää tämän elseä
    {
        board_ = new GameBoard;        //luodaan pelilautaolio oman attribuuttiosoittimen päähän, MUISTA DELETOIDA KUN DYNAAMINEN
        board_->init_empty();
        board_->fill(seed_);
        GAMEBOARD_EXISTS = true;

    }
    //else käännetään kaikki nollaan tai nullptr miten nyt ikinä, tai suoraan board.fill tms
}
//Haluan loopata läpi widgetit ja kirjoittaa niihin numbertilen arvon
void MainWindow::tietorakenne_graafiseksi()
{

    for ( int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            pair <int, int> koordinaatit (y, x);
            int numbertilen_arvo = board_->get_value(koordinaatit);
            QString arvo_tekstiksi = QString::number(numbertilen_arvo);
            pb_vektori.at(y).at(x)->setText(arvo_tekstiksi);

        }
    }
}



void MainWindow::on_resetPushButton_clicked() //Luennosta 47:00 gameboard_fill muokattava (if lause) tai tehtävä
                        //oma metodi resetille joka antaa tyhjät arvo ja pakottaa valitsemaan uudet siemenen ja goalin
{
    /*Uudelleenaloituksessa (reset) huomaa, että NumberTile-olioita ei kannata luoda uudelleen
     * (ks. GameBoard::fill) vaan antaa olemassa oleville olioille uudet (tyhjät) arvot.
     * Yksi vaihtoehto hoitaa asia on muokata edellä mainittua metodia hieman.
     * Tee kuitenkin muokkaus niin, että ohjelma toimii myös alkuperäisellä ei-GUI-käyttöliittymällä oikein.
     * Toinen vaihtoehto on toteuttaa toinen versio edellä mainitusta metodista.*/

   ui->seedSpinBox->setValue(0);
   ui->goalSpinBox->setValue(0);
   ui->textBrowser->setText("Nyt voi aloittaa pelin alusta, tässä ohjeet...:");

   //MUISTA GAMEBOARD_EXISTS VAKIO!!!
   //VOITTO JA HÄVIÄ PAKOTTAA TÄNNE, SEURAAVAKSI BACKENDISSÄ NUMBERTILIEN ARVOJEN MUUTTAMINEN JA UUDELLEEN ALUSTUS LÄHTÖTILANTEESEEN

   //init_empty_board() saattaa luoda uudet widgetit vanhojen päälle mutta sillä voi frontin hoitaa
   //filliä piti muuttaa
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
    }
    else if (board_->is_full())
    {
        havio_funktio();
    }
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    tietorakenne_graafiseksi();
}

//VALMIS
void MainWindow::on_rightPushButton_clicked()
{
    if (board_->move(RIGHT, goal_))
    {
        voitto_funktio();
    }
    else if (board_->is_full())
    {
        havio_funktio();
    }
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    tietorakenne_graafiseksi();
}

//VALMIS
void MainWindow::on_downPushButton_clicked()
{
    if (board_->move(DOWN, goal_))
    {
        voitto_funktio();
    }
    else if (board_->is_full())
    {
        havio_funktio();
    }
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    tietorakenne_graafiseksi();
}

//VALMIS
void MainWindow::on_leftPushButton_clicked()
{
    if (board_->move(LEFT, goal_))
    {
        voitto_funktio();
    }
    else if (board_->is_full())
    {
        havio_funktio();
    }
    board_->new_value(false);       //ihan täysin en ymmärrä miksi tuo false parametri on tarpeellinen
    tietorakenne_graafiseksi();
}

void MainWindow::voitto_funktio()
{
    QString tavoite = QString::number(goal_);
    ui->textBrowser->setText("You won! you reached the goal" +tavoite);
    //plus aktivoinnit&deaktivoinnit, mahdollisesti nollaus tästä tai resetistä
    //Ehkä pakotus resetiin deaktivoinneilla ja sieltä backendin alustus lähtötilanteeseen
}

void MainWindow::havio_funktio()
{
    ui->textBrowser->setText("You lost. Can't add a new tile.");
    //deaktivoinnit&aktivoinnit,  pakotus resetiin ja sieltä alustus lähtötilanteeseen
}


