#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <string>
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
    //void on_keyLineEdit_textEdited(const QString &arg1);

    void on_keyLineEdit_textChanged(const QString &arg1);


    void on_findPushButton_clicked();

    void on_fileLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString nimi_;
    QString tiedosto_;
};
#endif // MAINWINDOW_HH
