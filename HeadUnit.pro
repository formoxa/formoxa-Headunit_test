QT       += core gui
QT       += bluetooth
# 需要套件 qtconnectivity5-dev
QT       += multimedia multimediawidgets
# 需要套件 qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5
# Raspberry pi 若無聲音輸出，注意 gstreamer 相關套件是否安裝，安裝可參考官網
# libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-x gstreamer1.0-pulseaudio

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HeadUnit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    BluetoothDialog.cpp \
    AndroidBluetoothServer.cpp \
    SettingWindow.cpp \
    MusicPlayerWindow.cpp

HEADERS += \
    MainWindow.h \
    BluetoothDialog.h \
    AndroidBluetoothServer.h \
    SettingWindow.h \
    MusicPlayerWindow.h

FORMS += \
    MainWindow.ui \
    BluetoothDialog.ui \
    SettingWindow.ui \
    MusicPlayerWindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
