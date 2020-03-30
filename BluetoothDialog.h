#ifndef BLUETOOTHDIALOG_H
#define BLUETOOTHDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>

namespace Ui {
class BluetoothDialog;
}

class BluetoothDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BluetoothDialog(QWidget *parent = nullptr);
    ~BluetoothDialog();

private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo&);
    void searchStart();
    void searchFinish();
    void itemActivated(QListWidgetItem* item);

    void on_pushButton_Cancel_clicked();
    void on_pushButton_Search_clicked();
    void on_checkBox_BluetoothDiscoverable_stateChanged();

    void on_pushButton_Clean_clicked();

private:
    Ui::BluetoothDialog *ui;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothLocalDevice* localDevice;
};

#endif // BLUETOOTHDIALOG_H
