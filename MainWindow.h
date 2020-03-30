#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "boost/log/trivial.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void exit();
    void openSettings();
    void openMusicPlayer();

private slots:
    void showTime();
    void on_pushButton_Bluetooth_clicked();

    //void on_pushButton_Music_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
