#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Canvas jolle ruudut luodaan
    scene_ = new QGraphicsScene(this);
    int left_margin = 5;
    int top_margin = 5;

    //tää ei toimi
    scene_->setBackgroundBrush(Qt::blue);
    scene_->setSceneRect(left_margin, top_margin, 200, 200);


    ui->textBrowser->setText("Tervetuloa pelaamaan, tässä ohjeet...:");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Ihan eka tuo tietorakenne graafiseksi, graphicviewistä oli maininta ja saiko tehdä pelkästään labelilla, luennolta ohje?
//ALUSSA ILMAN ETTÄ MITÄÄN KLIKATAAN PITÄS SAADA RUUDUKKO (JA TEXTBROWSERIIN OHJEISTUSTEKSTI)

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
}



void MainWindow::on_startPushButton_clicked()
{
    //miten tarkistetaan että goal on hyväksyttävä, ohjelmakoodissa vai kälikooodissa
    //tarkista että goal on oikein  textbrowseriin ilmoitus ja ohjeistus jos ei ole
    //8192 on kolmastoista potenssi, ne vois kaikki 13 olla vaihtoehtoina

    if (seed_ > 0 and is_goal_approved())
    {
        ui->textBrowser->setText("Jepulis");
        //Luo backendissä tietorakenne ja kaikki tarvittava...

        //Mitä jos kävis tuon tietorakenteen läpi ja loisi labelit esim canvasille sen pohjalta suoraan
        //ja kun nuolinäppäimiä painetaan vie käskyn backendiin ja piirtää tietorakenteen uudelleen.., silloin
        //widgettejä piirretään koko ajan uusiksi
        //parempi tapa olisi varmaan muuttaa widgettien arvoa tietorakenteen pohjalta 0-2048 väliltä

    }
    else
        ui->textBrowser->setText("Siemenluvun täytyy olla suurempi kuin nolla ja tavoiteluvun "
                                        "jokin 2:n potenssi, kuitenkin maksimissaan 8192.");
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
}
//Tarkistaa onko tavoiteluku kakkosen potenssi
bool MainWindow::is_goal_approved()
{
    for (auto i : APPROVED_GOALS)
        if (goal_ == i)
            return true;
    return false;
}

/*Peliruudukon voi toteuttaa esimerkiksi QGraphicsScene-ominaisuutena sekä etiketteinä (label).
 * QGraphicsScene-ominaisuutta on käytetty liikkuvassa ympyrässä ja vesipisarapelissä, joten niistä voit katsoa mallia.

 *QGraphicsScene:lle voidaan asettaa erilaisia kuvioita kuten suorakulmioita tai ympyröitä.
 *Liikkuvan ympyrän esimerkissä sille asetettiin ympyrä, mutta tässä tarvitset suorakulmioita (QGraphicsRectItem).
 *Huomaa, että suorakulmioon ei voi asettaa tekstiä (lukuja), joten todennäköisesti tarvitset myös etikettejä (QLabel).*/

