#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>


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
    //Attribuutit
    Ui::MainWindow* ui;
            int seed_,
                goal_;

    // Attribuuttiosoitin backend-olioon.
     GameBoard* board_;

     // Tietorakenne peliruuduille
    vector<vector<QPushButton*>> pb_vektori;

    // Vakiomuuttujat
    const int ruudun_koko = 40;

    const vector<int> APPROVED_GOALS =
    {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    const map<int, QString> vari_kartta =
    {{0,"lightyellow"}, {2, "lightpink"}, {4, "lightsalmon"},
    {8, "lightsteelblue"}, {16, "lightskyblue"}, {32, "aqua"}, {64, "lightgreen"},
    {128, "lightseagreen"}, {256, "mediumseagreen"}, {512, "darkgreen"},
    {1024, "lightcoral"}, {2048, "indianred"}, {4096, "tomato"}, {8192, "violet"}};

    // Funktiot
    bool is_goal_approved();
    void widgetit_tietorakenteeseen_ja_ruudulle();
    void luo_backend_tai_palauttaa_alkutilanteeseen();
    void backend_tietorakenne_graafiseksi();
    void voitto_funktio();
    void havio_funktio();
    QString hae_laatikon_vari(int luku);


};
#endif // MAINWINDOW_HH
