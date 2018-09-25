#include "goatqueryform.h"
#include "ui_goatqueryform.h"

GoatQueryForm::GoatQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoatQueryForm)
{
    ui->setupUi(this);
    refreshFlag = 0;
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    changeDialog = new ChangeGoatInfoDialog(this);
    cmenu = new QMenu(ui->tableView);
    actionR3 = cmenu->addAction("绑定");
    actionR2 = cmenu->addAction("解绑");
    actionR4 = cmenu->addAction("设备故障");
    actionR1 = cmenu->addAction("删除");

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    //goatQueryHeaderModelInit();//表格头部初始化
    QSqlQuery query(DB::instance().data()->getDb());
    //query.exec("select distinct shehao from goatInfo;");
    query.exec("select * from houseInfo");
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }
    updateTableWidgest();
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTableWidgest()));
    connect(changeDialog,SIGNAL(refresh_table()),this,SLOT(updateTableWidgest()));

    connect(actionR1,SIGNAL(triggered(bool)),this,SLOT(deleteSelected()));
    connect(actionR2,SIGNAL(triggered(bool)),this,SLOT(unbindSelected()));
    connect(actionR3,SIGNAL(triggered(bool)),this,SLOT(bindSelected()));
    connect(actionR4,SIGNAL(triggered(bool)),this,SLOT(errorSelected()));
}

GoatQueryForm::~GoatQueryForm()
{
    delete ui;
}

void GoatQueryForm::updateTableWidgest(){

    refreshFlag = 0;
    QSqlQuery query;
   // query.prepare("select goatId as 山羊编号, shehao as 舍号, deviceId as 绑定设备id, weight as 体重, inTime as 入圈时间, outTime as 出圈时间 from goatInfo where shehao = :shehao;");
    query.prepare("select a.goatId as 奶山羊编号,ifnull(b.deviceId,'无') as 绑定设备id,a.houseId as 舍号,a.weight as 体重,a.inTime as 入圈时间,a.outTime as 出圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where a.houseId = :houseId;");
    query.bindValue(":houseId",ui->comboBox->currentText());
    query.exec();
    sqlQueryModel->setQuery(query);

    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}
void GoatQueryForm::showAllData(){

    refreshFlag = 1;
    sqlQueryModel->setQuery("select a.goatId as 奶山羊编号,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.weight as 体重,a.inTime as 入圈时间,a.outTime as 出圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId");


    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);


}

void GoatQueryForm::on_pushButton_2_clicked()
{
    showAllData();
}


void GoatQueryForm::on_pushButton_3_clicked()
{
    refreshFlag = 2;
    QSqlQuery query;
    query.prepare("select a.goatId as 奶山羊编号,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.weight as 体重,a.inTime as 入圈时间,a.outTime as 出圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where a.inTime >= :startTime and a.inTime <= :endTime;");
    query.bindValue(":startTime",ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":endTime",ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.exec();
    sqlQueryModel->setQuery(query);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);
    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void GoatQueryForm::on_pushButton_clicked()
{
    refreshFlag = 3;
    QSqlQuery query;
    query.prepare("select a.goatId as 奶山羊编号,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.weight as 体重,a.inTime as 入圈时间,a.outTime as 出圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where a.outTime >= :startTime and a.outTime <= :endTime;");
    query.bindValue(":startTime",ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":endTime",ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.exec();
    sqlQueryModel->setQuery(query);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);
    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
}

void GoatQueryForm::on_tableView_doubleClicked(const QModelIndex &index)
{
   // changeDialog->show();
    int row = index.row();
    QList<QString> list;
    for(int i = 0; i < ui->tableView->model()->columnCount();i++){
       list << ui->tableView->model()->index(row,i).data().toString();
    }
    changeDialog->fillData(list);
    changeDialog->show();
}

void GoatQueryForm::on_pushButton_4_clicked()
{
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    foreach (int temp, list) {
        qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }

}

void GoatQueryForm::deleteSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("delete from goatInfo where goatId = :goatId;");
    foreach (int temp, list) {
        query.bindValue(":goatId",ui->tableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    updateTableWidgest();
}

void GoatQueryForm::unbindSelected(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("delete from bindingInfo where goatId = :goatId;");
    foreach (int temp, list) {
        query.bindValue(":goatId",ui->tableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
    //updateTableWidgest();
}

void GoatQueryForm::bindSelected(){
    //emit goatIdSignal(ui->tableView->model()->index(ui->tableView->));
    emit goatIdSignal( ui->tableView->model()->index(ui->tableView->selectionModel()->selectedIndexes().at(0).row(),0).data().toString());
}

void GoatQueryForm::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    if(ui->tableView->selectionModel()->selectedIndexes().size() > 0){
        cmenu->exec(QCursor::pos());
    }
}

void GoatQueryForm::errorSelected(){
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
        delQuery.bindValue(":deviceId",ui->tableView->model()->index(temp,2).data().toInt());
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,2).data().toInt());
        delQuery.exec();
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void GoatQueryForm::refreshView(){
    switch (refreshFlag) {
    case 0:
        updateTableWidgest();
        break;
    case 1:
        showAllData();
        break;
    case 2:
        on_pushButton_3_clicked();
        break;
    case 3:
        on_pushButton_clicked();
        break;
    default:
        updateTableWidgest();
        break;
    }
}
