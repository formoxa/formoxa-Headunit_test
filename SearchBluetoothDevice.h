#ifndef SEARCHBLUETOOTHDEVICE_H
#define SEARCHBLUETOOTHDEVICE_H

#include <QBluetoothDeviceDiscoveryAgent>

class SearchBluetoothDevice : public QObject
{
public:
    SearchBluetoothDevice();

signals:
    void deviceDiscovered(const QBluetoothDeviceInfo&);

private:
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
};

#endif // SEARCHBLUETOOTHDEVICE_H
