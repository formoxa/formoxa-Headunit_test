#include "SearchBluetoothDevice.h"


SearchBluetoothDevice::SearchBluetoothDevice()
{
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    discoveryAgent->start();
}

void SearchBluetoothDevice::deviceDiscovered(const QBluetoothDeviceInfo& deviceInfo)
{

}
