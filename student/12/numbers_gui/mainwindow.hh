#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>   //Tuotu iha ite

using namespace std;

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

private:
    Ui::MainWindow *ui;     //osoitin pääikkunaa, toimii parenttina muille widgeteille
    int seed_,
        goal_;
    QGraphicsScene* scene_; //osoitin canvasiin

    const vector<int> APPROVED_GOALS =
    {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
    bool is_goal_approved();
};
#endif // MAINWINDOW_HH
