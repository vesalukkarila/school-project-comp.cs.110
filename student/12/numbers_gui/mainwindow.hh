#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QGraphicsScene>   //Tuotu iha ite, poisto?
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

//static bool GAMEBOARD_EXISTS = false;

using namespace std;

class GameBoard;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seedSpinBox_valueChanged(int arg1);

    void on_goalSpinBox_valueChanged(int arg1);

    void on_startPushButton_clicked();

    void on_resetPushButton_clicked();


    void on_upPushButton_clicked();

    void on_rightPushButton_clicked();

    void on_downPushButton_clicked();

    void on_leftPushButton_clicked();


private:
    Ui::MainWindow *ui;     //osoitin pääikkunaa, toimii parenttina muille widgeteille
    int seed_,
        goal_;
    QGraphicsScene* scene_; //osoitin canvasiin joka graphicsviewin sisällä
    QGridLayout* grid_lay_out_;

    vector<vector<QPushButton*>> pb_vektori;
    const int ruudun_koko = 40;

    GameBoard* board_;          //Katso että tuhotaan dynaaminen olio

    const vector<int> APPROVED_GOALS =
    {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
    bool is_goal_approved();
    void widgetit_tietorakenteeseen_ja_ruudulle();
    void luo_backend_tai_palauttaa_alkutilanteeseen();
    void backend_tietorakenne_graafiseksi();
    void voitto_funktio();
    void havio_funktio();
    QString hae_laatikon_vari(int luku);

    const map<int, QString> vari_kartta =           //Saako tämän alustaa täällä, oli joku läppä asiasta mitä .hh:ssa saa tehdä
    {{0,"lightyellow"}, {2, "blue"}, {4, "green"},
    {8, "red"}, {16, "blue"}, {32, "green"}, {64, "blue"},
    {128, "blue"}, {256, "blue"}, {512, "blue"}, {1024, "blue"},
    {2048, "blue"}, {4096, "blue"}, {8192, "blue"} };
};
#endif // MAINWINDOW_HH
