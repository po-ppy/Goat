#include "devicequeryform.h"
#include "ui_devicequeryform.h"

DeviceQueryForm::DeviceQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceQueryForm)
{
    ui->setupUi(this);
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    //ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    //ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    QSqlQuery query(DB::instance().data()->getDb());
    query.exec("select * from houseInfo");
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }
    showAllData();
    //connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTableWidgest()));
    //connect(changeDialog,SIGNAL(refresh_table()),this,SLOT(updateTableWidgest()));
}

DeviceQueryForm::~DeviceQueryForm()
{
    delete ui;
}

void DeviceQueryForm::updateTableWidgest(){
    QSqlQuery query;
    query.prepare("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId where b.houseId = :houseId;");
    query.bindValue(":houseId",ui->comboBox->currentText());
    query.exec();
    sqlQueryModel->setQuery(query);
    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void DeviceQueryForm::showAllData(){
    sqlQueryModel->setQuery("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId;",DB::instance().data()->getDb());
    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void DeviceQueryForm::updateTableWidgestByState(){
    QSqlQuery query;
    query.prepare("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId where a.deviceState = :deviceState;");
    query.bindValue(":deviceState",ui->comboBox_2->currentText());
    query.exec();
    sqlQueryModel->setQuery(query);
    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void DeviceQueryForm::on_pushButton_clicked()
{
    showAllData();
}

void DeviceQueryForm::on_comboBox_currentIndexChanged(const QString &arg1)
{
    updateTableWidgest();
}

void DeviceQueryForm::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    updateTableWidgestByState();
}

void DeviceQueryForm::on_comboBox_activated(const QString &arg1)
{
    updateTableWidgest();
}

void DeviceQueryForm::on_comboBox_2_activated(const QString &arg1)
{
    updateTableWidgestByState();
}
