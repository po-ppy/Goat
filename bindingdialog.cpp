#include "bindingdialog.h"
#include "ui_bindingdialog.h"

bindingDialog::bindingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bindingDialog)
{
    ui->setupUi(this);
    goatSqlQueryModel = new QSqlQueryModel(this);
    goatSortFilterProxyModel = new QSortFilterProxyModel(this);

    deviceSqlQueryModel = new QSqlQueryModel(this);
    deviceSortFilterProxyModel = new QSortFilterProxyModel(this);

    qSqlQuery = new QSqlQuery(DB::instance().data()->getDb());
    qSqlQuery->prepare("insert into bindingInfo(goatId ,deviceId) values(:goatId ,:deviceId) on duplicate key update goatId=values(goatId),deviceId=values(deviceId);");
    updateGoatTable();
    updateDeviceTable();

}

bindingDialog::~bindingDialog()
{
    delete ui;
}

void bindingDialog::updateGoatTable(){
    if(ui->goatCheckBox->isChecked()){
        goatSqlQueryModel->setQuery("select a.goatId as 编号,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.inTime as 入圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where b.deviceId is NULL;");
    }else{
        goatSqlQueryModel->setQuery("select a.goatId as 编号,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.inTime as 入圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId;");
    }
    goatSortFilterProxyModel->setDynamicSortFilter(true);
    goatSortFilterProxyModel->setSourceModel(goatSqlQueryModel);

    ui->goatTableView->setModel(goatSortFilterProxyModel);
    ui->goatTableView->setSortingEnabled(true);
    ui->goatTableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void bindingDialog::updateDeviceTable(){
    if(ui->deviceCheckBox->isChecked()){
        deviceSqlQueryModel->setQuery("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId where a.deviceState = '闲置';");
    }else{
        deviceSqlQueryModel->setQuery("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId where a.deviceState <> '故障';");
    }
    deviceSortFilterProxyModel->setDynamicSortFilter(true);
    deviceSortFilterProxyModel->setSourceModel(deviceSqlQueryModel);

    ui->deviceTableView->setModel(deviceSortFilterProxyModel);
    ui->deviceTableView->setSortingEnabled(true);
    ui->deviceTableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void bindingDialog::on_goatCheckBox_stateChanged(int arg1)
{
    updateGoatTable();
}

void bindingDialog::on_deviceCheckBox_stateChanged(int arg1)
{
    updateDeviceTable();
}

void bindingDialog::on_doubleButton_clicked()
{
    ui->confirmButton->setEnabled(!ui->confirmButton->isEnabled());
}

void bindingDialog::on_goatTableView_doubleClicked(const QModelIndex &index)
{
    ui->goatSelected->setText(ui->goatTableView->model()->index(index.row(),0).data().toString());
    if(ui->deviceSelected->text() != ""){
        if(!ui->confirmButton->isEnabled()){
            startBinding();
        }
    }
}

void bindingDialog::on_deviceTableView_doubleClicked(const QModelIndex &index)
{
    ui->deviceSelected->setText(ui->deviceTableView->model()->index(index.row(),0).data().toString());
    if(ui->goatSelected->text() != ""){
        if(!ui->confirmButton->isEnabled()){
            startBinding();
        }
    }
}

void bindingDialog::startBinding(){
    qSqlQuery->bindValue(":goatId",ui->goatSelected->text().trimmed());
    qSqlQuery->bindValue(":deviceId",ui->deviceSelected->text().trimmed());
    if(qSqlQuery->exec()){
        ui->bindingResult->setText("奶山羊("+ui->goatSelected->text()+") 和 设备("+ui->deviceSelected->text()+") 绑定成功 。");
        ui->bindingResult->setStyleSheet("color:green;");
        ui->goatSelected->setText("");
        ui->deviceSelected->setText("");
        emit updateSignal();
        //updateGoatTable();
        //updateDeviceTable();
    }else{
        ui->bindingResult->setText("绑定失败！");
        ui->bindingResult->setStyleSheet("color:red;");
    }

}

void bindingDialog::on_confirmButton_clicked()
{
    if(ui->goatSelected->text() != "" && ui->deviceSelected->text() != ""){
        startBinding();
    }else{
        ui->bindingResult->setText("编号非法！");
        ui->bindingResult->setStyleSheet("color:red;");
    }
}

void bindingDialog::receiveGoatId(QString goatId){
    if(!this->isVisible()){
        this->show();
    }
    ui->goatSelected->setText(goatId);
}

void bindingDialog::receiveDeviceId(QString deviceId){
    if(!this->isVisible()){
        this->show();
    }
    ui->deviceSelected->setText(deviceId);
}
