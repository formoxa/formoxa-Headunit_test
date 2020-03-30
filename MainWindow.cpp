#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BluetoothDialog.h"
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //連結按鍵功能
    QObject::connect(ui->pushButton_Exit, &QPushButton::clicked, this, &MainWindow::exit);
    QObject::connect(ui->pushButton_Setting, &QPushButton::clicked, this, &MainWindow::openSettings);
    QObject::connect(ui->pushButton_Music, &QPushButton::clicked, this, &MainWindow::openMusicPlayer);

    //顯示時間
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

//顯示現在時間
void MainWindow::showTime()
{

    ui->label_DateTime->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd  AP H:mm"));
}

void MainWindow::on_pushButton_Bluetooth_clicked()
{
    //建立藍芽視窗
    BluetoothDialog bluetoothDialog;
    //設定藍芽視窗必須先關閉才能控制其他視窗
    bluetoothDialog.setModal(true);
    //開啟藍芽視窗
    bluetoothDialog.exec();
}

/*void MainWindow::on_pushButton_Music_clicked()
{
    //建立音樂撥放器視窗
    MusicPlayerDialog musicPlayerDialog;
    musicPlayerDialog.setModal(false);
    //開啟藍芽視窗
    musicPlayerDialog.exec();
}*/
