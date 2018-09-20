#include "devicequeryform.h"
#include "ui_devicequeryform.h"

DeviceQueryForm::DeviceQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceQueryForm)
{
    ui->setupUi(this);
    refreshFlag = 0;
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);

    cmenu = new QMenu(ui->tableView);
    actionR1 = cmenu->addAction("绑定");
    actionR2 = cmenu->addAction("解绑");
    actionR3 = cmenu->addAction("设备故障");
    actionR4 = cmenu->addAction("恢复使用");
    actionR5 = cmenu->addAction("删除");

    connect(actionR1,SIGNAL(triggered(bool)),this,SLOT(bindSelected()));
    connect(actionR2,SIGNAL(triggered(bool)),this,SLOT(unbindSelected()));
    connect(actionR3,SIGNAL(triggered(bool)),this,SLOT(errorSelected()));
    connect(actionR4,SIGNAL(triggered(bool)),this,SLOT(restartSelected()));
    connect(actionR5,SIGNAL(triggered(bool)),this,SLOT(deleteSelected()));

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
    refreshFlag = 0;
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
    refreshFlag = 1;
    sqlQueryModel->setQuery("select a.deviceId as 设备编号,a.deviceState as 设备状态,ifnull(b.goatId,'无') as 绑定山羊编号,ifnull(b.houseId,'无') as 舍号,a.inTime as 购入时间 from deviceInfo a left join bindingInfo c on a.deviceId = c.deviceId left join goatInfo b on b.goatId = c.goatId;",DB::instance().data()->getDb());
    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void DeviceQueryForm::updateTableWidgestByState(){
    refreshFlag = 2;
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

void DeviceQueryForm::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    if(ui->tableView->selectionModel()->selectedIndexes().size() > 0){
        cmenu->exec(QCursor::pos());
    }
}

void DeviceQueryForm::bindSelected(){
    emit deviceIdSignal(ui->tableView->model()->index(ui->tableView->selectionModel()->selectedIndexes().at(0).row(),0).data().toString());
}

void DeviceQueryForm::unbindSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("delete from bindingInfo where deviceId = :deviceId;");
    foreach (int temp, list) {
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void DeviceQueryForm::errorSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    QSqlQuery delQuery;
    //query.prepare("delete from bindingInfo where goatId = :goatId;");
    delQuery.prepare("delete from bindingInfo where deviceId = :deviceId;");
    query.prepare("update deviceInfo set deviceState = '故障' where deviceId = :deviceId;");
    foreach (int temp, list) {
        delQuery.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data().toInt());
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data().toInt());
        delQuery.exec();
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void DeviceQueryForm::restartSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("update deviceInfo set deviceState = '闲置' where deviceId = :deviceId;");
    foreach (int temp, list) {
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data().toInt());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void DeviceQueryForm::deleteSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("delete from deviceInfo where deviceId = :deviceId;");
    foreach (int temp, list) {
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void DeviceQueryForm::refreshView(){
    switch (refreshFlag) {
    case 0:
        updateTableWidgest();
        break;
    case 1:
        showAllData();
        break;
    case 2:
        updateTableWidgestByState();
        break;
    default:
        updateTableWidgest();
        break;
    }
}
