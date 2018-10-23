#include "goatqueryform.h"
#include "ui_goatqueryform.h"

GoatQueryForm::GoatQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoatQueryForm)
{
    ui->setupUi(this);
    refreshFlag = 1;
    sqlQueryModel = new QSqlQueryModel(this);
    houseQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    changeDialog = new ChangeGoatInfoDialog(this);
    addGoatDialog = new AddGoatDialog(this);
    cmenu = new QMenu(ui->tableView);
    actionR3 = cmenu->addAction("绑定");
    actionR2 = cmenu->addAction("解绑");
    actionExport = cmenu->addAction("导出");
    actionR4 = cmenu->addAction("设备故障");
    actionMoveToHouse = cmenu->addAction("移舍");
    actionR1 = cmenu->addAction("删除");

    houseMenu = new QMenu(ui->houseIdTableView);
    actionRenameHouse = houseMenu->addAction("重命名");
    actionAddHouse = houseMenu->addAction("添加新舍");
    actionDeleteHouse = houseMenu->addAction("删除");

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    //updateTableWidgest();
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTableWidgest()));
    connect(changeDialog,SIGNAL(refresh_table()),this,SLOT(updateTableWidgest()));

    connect(actionR1,SIGNAL(triggered(bool)),this,SLOT(deleteSelected()));
    connect(actionR2,SIGNAL(triggered(bool)),this,SLOT(unbindSelected()));
    connect(actionR3,SIGNAL(triggered(bool)),this,SLOT(bindSelected()));
    connect(actionR4,SIGNAL(triggered(bool)),this,SLOT(errorSelected()));
    connect(actionMoveToHouse,SIGNAL(triggered(bool)),this,SLOT(moveToHouse()));

    connect(actionAddHouse,SIGNAL(triggered(bool)),this,SLOT(addHouseId()));
    connect(actionDeleteHouse,SIGNAL(triggered(bool)),this,SLOT(deleteHouseId()));
    connect(actionRenameHouse,SIGNAL(triggered(bool)),this,SLOT(renameHouseId()));
    connect(actionExport,SIGNAL(triggered(bool)),this,SLOT(exportToFile()));
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

void GoatQueryForm::showNoHouseGoat(){
    refreshFlag = 4;
    sqlQueryModel->setQuery("select a.goatId as 奶山羊编号,ifnull(b.deviceId ,'无') as 绑定设备编号,a.houseId as 舍号,a.weight as 体重,a.inTime as 入圈时间,a.outTime as 出圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where a.houseId is null;");


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
    addMoreHouseId();
}

void GoatQueryForm::deleteSelected(){
    int confirm = QMessageBox::question(this,"确认","确定删除选中奶山羊吗?",QMessageBox::Yes,QMessageBox::No);
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
    query.prepare("delete from goatInfo where goatId = :goatId;");
    foreach (int temp, list) {
        query.bindValue(":goatId",ui->tableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    //updateTableWidgest();
    emit updateSignal();
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
        delQuery.bindValue(":deviceId",ui->tableView->model()->index(temp,2).data());
        query.bindValue(":deviceId",ui->tableView->model()->index(temp,2).data());
        delQuery.exec();
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void GoatQueryForm::moveToHouse(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    QList<QString> goatlist;
    foreach(QModelIndex temp, tempList){
        if(!goatlist.contains(ui->tableView->model()->index(temp.row(),0).data().toString())){
            goatlist.append(ui->tableView->model()->index(temp.row(),0).data().toString());
        }
    }
    QList<QString> houseList;
    QSqlQuery query;
    query.exec("select * from houseInfo;");
    while(query.next()){
        houseList.append(query.value("houseId").toString());
    }
    bool ok = false;
    QString newHouse = QInputDialog::getItem(this,"移动","选择移入的舍号:",houseList,0,false,&ok);
    if(ok && !newHouse.isEmpty()){
        query.prepare("update goatInfo set houseId = :houseId where goatId = :goatId;");

        foreach (QString temp, goatlist) {
            query.bindValue(":houseId",newHouse);
            query.bindValue(":goatId",temp);
            if(!query.exec()){
                qDebug() << "houseData数据库插入失败！";
               qDebug() << query.lastQuery();
                 QSqlError err;
               err= query.lastError();
                qDebug() << err.text();
            }
        }
    }
    emit updateSignal();
}

void GoatQueryForm::refreshView(){
    updateHouseId();
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
    case 4:
        showNoHouseGoat();
        break;
    default:
        qDebug() << refreshFlag;
        updateTableWidgest();
        break;
    }
}

void GoatQueryForm::updateHouseId(){
    int runFlag = refreshFlag;
    QString curText = ui->comboBox->currentText();
    ui->comboBox->clear();
    QSqlQuery query(DB::instance().data()->getDb());
    query.exec("select houseId as 舍号 from houseInfo");
    houseQueryModel->setQuery(query);
    ui->houseIdTableView->setModel(houseQueryModel);
    ui->houseIdTableView->horizontalHeader()->setStretchLastSection(true);
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

void GoatQueryForm::addHouseId(){
    QSqlQuery query;
    bool ok = false;
    QString newName = QInputDialog::getText(this,"请输入新舍命","新舍名:",QLineEdit::Normal,"",&ok);
    if(ok && !newName.isEmpty()){
        query.prepare("select houseId from houseInfo where houseId = :houseId;");
        query.bindValue(":houseId",newName);
        if(query.size()>0){
            QMessageBox::warning(this,"警告","此舍命已存在!!");
            return;
        }
    }
    query.prepare("insert into houseInfo(houseId) values(:houseId);");
    query.bindValue(":houseId",newName);
    if(query.exec()){
        QMessageBox::information(this,"成功","添加新舍成功!");
        emit updateSignal();
    }else{
        QMessageBox::warning(this,"失败","添加新舍失败!");
    }

}

void GoatQueryForm::renameHouseId(){
    QSqlQuery query;
    bool ok = false;
    QString newName = QInputDialog::getText(this,"请输入新舍命","新舍名:",QLineEdit::Normal,"",&ok);
    if(ok && !newName.isEmpty()){
        query.prepare("select houseId from houseInfo where houseId = :houseId;");
        query.bindValue(":houseId",newName);
        if(query.size()>0){
            QMessageBox::warning(this,"警告","此舍命已存在!!");
            return;
        }
        query.prepare("update houseInfo set houseId = :newHouseId where houseId = :houseId;");
        query.bindValue(":houseId",ui->houseIdTableView->model()->index(ui->houseIdTableView->selectionModel()->selectedIndexes().at(0).row(),0).data().toString());
        query.bindValue(":newHouseId",newName);
        if(query.exec()){
            emit updateSignal();
            QMessageBox::information(this,"成功","羊舍重命名成功");
        }else{
            QMessageBox::warning(this,"失败","数据库错误!");
        }
    }
}

void GoatQueryForm::deleteHouseId(){
    int confirm = QMessageBox::question(this,"确认","确定删除选中羊舍吗?",QMessageBox::Yes,QMessageBox::No);
    if(confirm != QMessageBox::Yes){
        return;
    }
    QModelIndexList tempList = ui->houseIdTableView->selectionModel()->selectedIndexes();
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }

    QSqlQuery query;
    query.prepare("delete from houseInfo where houseId = :houseId;");
    foreach (int temp, list) {
        query.bindValue(":houseId",ui->houseIdTableView->model()->index(temp,0).data().toString());
        query.exec();
        //qDebug() << ui->tableView->model()->index(temp,0).data().toString();
    }
    emit updateSignal();
}

void GoatQueryForm::addMoreHouseId(){
    bool ok = false;
    int num = QInputDialog::getInt(this,"批量添加","输入填数量",1,1,1000,1,&ok);
    QSqlQuery query;
    query.exec("select count(houseId) as housenum from houseInfo");
    if(query.next()){
        int start = query.value("housenum").toInt()+1;
        int count = 0;
        while(count < num){
            QString newName = "舍"+QString::number(start);
            query.prepare("select * from houseInfo where houseId = :houseId;");
            query.bindValue(":houseId",newName);
            if(query.exec()){
                if(query.size()>0){
                    start += 1;
                }else{
                    query.prepare("insert into houseInfo(houseId) values(:houseId);");
                    query.bindValue(":houseId",newName);
                    if(query.exec()){
                        start += 1;
                        count += 1;
                    }else{
                        emit updateSignal();
                        QMessageBox::warning(this,"失败","数据库出错，添加终止!!");
                        return;
                    }
                }
            }else{
                emit updateSignal();
                QMessageBox::warning(this,"失败","数据库出错，添加终止!!");
                return;
            }
        }
    }
    emit updateSignal();
}

void GoatQueryForm::on_houseIdTableView_customContextMenuRequested(const QPoint &pos)
{
    if(ui->houseIdTableView->selectionModel()->selectedIndexes().size() > 0){
        houseMenu->exec(QCursor::pos());
    }
}

void GoatQueryForm::on_addNewHosueButton_clicked()
{
    addHouseId();
}

void GoatQueryForm::on_addGoatButton_clicked()
{
    addGoat();
}

void GoatQueryForm::on_addFromFileButton_clicked()
{
    addFromFile();
}

void GoatQueryForm::on_exportButton_clicked()
{
    exportToFile();
}

void GoatQueryForm::addGoat(){
    addGoatDialog->show();
    addGoatDialog->onShowOut();
}

void GoatQueryForm::addFromFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("打开"),".",tr("文本文档(*.txt)"));
    if(!filePath.isNull()){
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            //qDebug() << "start add from file";
            QList<QString> errList;
            int count = 0;
            while(!file.atEnd()){
                QList<QString> tempLineList = QString::fromLocal8Bit(file.readLine()).remove("\n").split(" ");
                tempLineList.removeAll("");
                tempLineList.removeAll(" ");
                //qDebug() << tempLineList.length();
                if(tempLineList.length() == 3){
                    QSqlQuery query;
                    query.prepare("insert into goatInfo(goatId,weight,houseId,inTime) values(:goatId,:weight,:houseId,now());");
                    query.bindValue(":goatId",tempLineList.at(0));
                    query.bindValue(":weight",tempLineList.at(1).toFloat());
                    query.bindValue(":houseId",tempLineList.at(2));
                    if(!query.exec()){
                        errList.append(tempLineList.at(0));
                    }else{
                        count += 1;
                    }
                }
            }
            //qDebug() << "end add from file";
            file.close();
            emit updateSignal();
            //refreshView();
            QMessageBox::information(this,"结果",QString::number(count)+"条导入成功,"+QString::number(errList.length())+"条导入失败。(失败信息保存在剪切板中)");
            if(errList.length() > 0){
                QClipboard *tempboard = QApplication::clipboard();
                QString temp = "";
                foreach (QString elem, errList) {
                    temp += elem + "\n";
                }
                tempboard->setText("导入失败奶山羊编号如下:\n"+temp);

            }
        }else{
            qDebug() << "open error!";
        }
    }

}

void GoatQueryForm::exportToFile(){
    QModelIndexList tempList = ui->tableView->selectionModel()->selectedIndexes();
    if(tempList.size() < 1){
        QMessageBox::warning(this,"警告","请先选择要导出的奶山羊!");
        return;
    }
    QList<int> list;
    foreach(QModelIndex temp, tempList){
        if(!list.contains(temp.row())){
            list.append(temp.row());
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,tr("打开"),".",tr("文本文档(*.txt)"));
    if(!filePath.isNull()){
        QFile file(filePath);
        if(!file.open((QIODevice::WriteOnly | QIODevice::Text))){
            qDebug() << "Open failed!";
        }else{
            QTextStream fileOut(&file);
            foreach (int temp, list) {
                for(int i = 0;i<ui->tableView->model()->columnCount();i++){
                    fileOut << ui->tableView->model()->index(temp,i).data().toString().toLocal8Bit() << " ";
                }
                fileOut << "\n";
            }
            file.close();
        }
    }
}
