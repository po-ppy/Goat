#include "devicequeryform.h"
#include "ui_devicequeryform.h"

DeviceQueryForm::DeviceQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceQueryForm)
{
    ui->setupUi(this);
    refreshFlag = 1;
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);

    cmenu = new QMenu(ui->tableView);
    actionR1 = cmenu->addAction("绑定");
    actionR2 = cmenu->addAction("解绑");
    actionR6 = cmenu->addAction("导出");
    actionR3 = cmenu->addAction("设备故障");
    actionR4 = cmenu->addAction("恢复使用");
    actionR5 = cmenu->addAction("删除");

    connect(actionR1,SIGNAL(triggered(bool)),this,SLOT(bindSelected()));
    connect(actionR2,SIGNAL(triggered(bool)),this,SLOT(unbindSelected()));
    connect(actionR3,SIGNAL(triggered(bool)),this,SLOT(errorSelected()));
    connect(actionR4,SIGNAL(triggered(bool)),this,SLOT(restartSelected()));
    connect(actionR5,SIGNAL(triggered(bool)),this,SLOT(deleteSelected()));
    connect(actionR6,SIGNAL(triggered(bool)),this,SLOT(exportSelected()));
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

void DeviceQueryForm::exportSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"打开",".","文本文档(*.txt)");
    if(filePath.isNull()){
        return;
    }
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,"警告","文件打开失败!");
        return;
    }
    QTextStream outStream(&file);
    foreach (int temp, list) {
        outStream << ui->tableView->model()->index(temp,0).data().toString().toLocal8Bit() << " " << ui->tableView->model()->index(temp,2).data().toString().toLocal8Bit() << " " << ui->tableView->model()->index(temp,4).data().toString().toLocal8Bit() << "\n";
    }
    file.close();
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
        delQuery.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data());
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data());
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
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,0).data());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void DeviceQueryForm::deleteSelected(){
    int confirm = QMessageBox::question(this,"确认","确定删除选中设备吗?",QMessageBox::Yes,QMessageBox::No);
    if(confirm != QMessageBox::Yes){
        return;
    }
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
    updateHouseId();
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

void DeviceQueryForm::updateHouseId(){
    int runFlag = refreshFlag;
    QString curText = ui->comboBox->currentText();
    ui->comboBox->clear();
    QSqlQuery query(DB::instance().data()->getDb());
    query.exec("select * from houseInfo");
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }
    if(!curText.isNull()){
        if(ui->comboBox->findText(curText) > -1){
            ui->comboBox->setCurrentText(curText);
        }
    }
    refreshFlag = runFlag;
}
