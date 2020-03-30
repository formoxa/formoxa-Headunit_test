#ifndef ANDROIDBLUETOOTHSERVER_H
#define ANDROIDBLUETOOTHSERVER_H

#include <memory>
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothServiceInfo>

class AndroidBluetoothServer : public QObject
{
    Q_OBJECT

public:
    AndroidBluetoothServer();
    void startServer(const QBluetoothAddress& localDeviceAddress);
    bool stopServer();

private slots:
    void onClientConnected();

private:
    std::unique_ptr<QBluetoothServer> rfcommServer_;
    QBluetoothServiceInfo serviceInfo_;
};

#endif // ANDROIDBLUETOOTHSERVER_H
