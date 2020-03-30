#include "BluetoothDialog.h"
#include "ui_BluetoothDialog.h"
#include <QList>
#include <QDebug>

BluetoothDialog::BluetoothDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BluetoothDialog)
{
    ui->setupUi(this);

    //設定一個本機藍芽裝置及一個藍芽搜尋器
    localDevice = new QBluetoothLocalDevice(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    //藍芽是否可被搜尋狀態在 Checkbox 呈現
    localDevice->hostMode() == QBluetoothLocalDevice::HostDiscoverable ? ui->checkBox_BluetoothDiscoverable->setChecked(true) : ui->checkBox_BluetoothDiscoverable->setChecked(false);

    //設定當偵測到一個藍芽裝置時將藍芽位置及名稱加入列表
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    QObject::connect(discoveryAgent, SIGNAL(finished()), this, SLOT(searchFinish()));
    //點擊並配對藍芽列表內該裝置
    QObject::connect(ui->listWidget_DiscoveredDevices, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(itemActivated(QListWidgetItem*)));


}

BluetoothDialog::~BluetoothDialog()
{
    delete ui;
}

//偵測到藍芽裝置時將藍芽位置及名稱加入列表
void BluetoothDialog::deviceDiscovered(const QBluetoothDeviceInfo& deviceInfo)
{
    //將藍芽 MAC 及名稱存在 Qstring 內
    QString label = QString("%1\t%2").arg(deviceInfo.address().toString()).arg(deviceInfo.name());
    //設定一個型態為QListWidgetItem 的 List，存放現有 ListWidget 內容物與 QString 比對結果
    QList<QListWidgetItem*> items = ui->listWidget_DiscoveredDevices->findItems(label,Qt::MatchExactly);
    //若比對結果不相符 (empty) 則為測得新裝置，並加入ListWidget 內
    if(items.empty())
    {
        QListWidgetItem* item = new QListWidgetItem(label);
        //偵測與本機配對狀態，配對中文字設為紅色，未配對則為黑色
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(deviceInfo.address());
        if(pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired)
        {
            item->setTextColor(QColor(Qt::red));
        }else{
            item->setTextColor(QColor(Qt::black));
        }
        ui->listWidget_DiscoveredDevices->addItem(item);
    }
}

void BluetoothDialog::searchStart()
{
    //開始偵測藍芽裝置
    discoveryAgent->start();
    //偵測時以下按鈕不可使用
    ui->pushButton_Search->setEnabled(false);
    ui->pushButton_Clean->setEnabled(false);
}

void BluetoothDialog::searchFinish()
{
    ui->pushButton_Search->setEnabled(true);
    ui->pushButton_Clean->setEnabled(true);
}

void BluetoothDialog::itemActivated(QListWidgetItem* item)
{
    //將點選的項目轉成文字並分拆為 Address 及 Name
    QString text = item->text();
    int index = text.indexOf("\t");
    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));
    //向 Address 要求配對
    localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
}

void BluetoothDialog::on_pushButton_Cancel_clicked()
{
    if(discoveryAgent->isActive()) discoveryAgent->stop();
    this->close();
}

void BluetoothDialog::on_pushButton_Clean_clicked()
{
    ui->listWidget_DiscoveredDevices->clear();
}

void BluetoothDialog::on_pushButton_Search_clicked()
{
    searchStart();
}

void BluetoothDialog::on_checkBox_BluetoothDiscoverable_stateChanged()
{
    if(ui->checkBox_BluetoothDiscoverable->isChecked())
    {
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }else{
        localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
    }
}
