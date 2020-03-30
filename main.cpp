#include "MainWindow.h"
#include "SettingWindow.h"
#include "MusicPlayerWindow.h"
#include <QApplication>
#include <QBluetoothLocalDevice>
#include "AndroidBluetoothServer.h"


int main(int argc, char *argv[])
{
    //===== Initial Process
    //啟用藍芽及建立藍芽 Server
    /*QBluetoothLocalDevice localDevice;
    const QBluetoothAddress address = localDevice.address();
    AndroidBluetoothServer androidBluetoothServer;
    androidBluetoothServer.startServer(address);*/

    //=====

    QApplication qApplication(argc, argv);

    //生成主視窗
    /*MainWindow mainWindow;
    mainWindow.setGeometry(QRect(0, 0, 800, 480));
    mainWindow.show();

    //生成設定視窗
    SettingWindow settingWindow;
    settingWindow.setGeometry(mainWindow.geometry());
    settingWindow.hide();*/

    //生成音樂撥放器視窗
    MusicPlayerWindow musicPlayerWindow;
    //musicPlayerWindow.setGeometry(mainWindow.geometry());
    musicPlayerWindow.show();

    //連結按鍵功能
    /*QObject::connect(&mainWindow, &MainWindow::exit, [](){std::exit(0);});
    QObject::connect(&mainWindow, &MainWindow::openSettings, &settingWindow, &SettingWindow::show);
    QObject::connect(&mainWindow, &MainWindow::openMusicPlayer, &musicPlayerWindow, &MusicPlayerWindow::show);*/


    qApplication.exec();

    //===== Shutdown Process
    //關閉藍芽 Server
    /*androidBluetoothServer.stopServer();*/

    //=====

    return 0;
}

