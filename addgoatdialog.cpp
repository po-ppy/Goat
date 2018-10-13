#include "addgoatdialog.h"
#include "ui_addgoatdialog.h"

AddGoatDialog::AddGoatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGoatDialog)
{
    ui->setupUi(this);

}

AddGoatDialog::~AddGoatDialog()
{
    delete ui;
}

bool AddGoatDialog::checkDB(){
    QSqlQuery query;
    return query.exec("select * from houseInfo;");
}

QString AddGoatDialog::createGoatId(){
    QSqlQuery query;
    if(query.exec("select count(goatId) as goatnum from goatInfo;")){
        if(query.next()){
            bool createFlag = true;
            int start = 10001 + query.value("goatnum").toInt();
            query.prepare("select goatId from goatInfo where goatId = :goatId;");
            while(createFlag){
                QString newGoatId = "G"+QString::number(start);
                query.bindValue(":goatId",newGoatId);
                if(query.exec()){
                    if(query.size() < 1){
                        return newGoatId;
                    }else{
                        start += 1;
                    }
                }else{
                    createFlag = false;
                }
            }
        }
    }
    return NULL;
}

void AddGoatDialog::loadHouseId(){
    ui->houseIdComboBox->clear();
    QSqlQuery query;
    if(query.exec("select * from houseInfo;")){
        while(query.next()){
            ui->houseIdComboBox->addItem(query.value("houseId").toString());
        }
    }
}

void AddGoatDialog::on_pushButton_clicked()
{
    ui->goatIdLineEdit->setEnabled(!ui->goatIdLineEdit->isEnabled());
}

void AddGoatDialog::onShowOut(){
    if(checkDB()){
        ui->goatIdLineEdit->setText(createGoatId());
        loadHouseId();
    }else{
        ui->goatIdLineEdit->setText("请先登录");
    }
}

bool AddGoatDialog::checkGoatId(){
    QSqlQuery query;
    query.prepare("select * from goatInfo where goatId = :goatId;");
    //ui->goatIdLineEdit->text();
    query.bindValue(":goatId",ui->goatIdLineEdit->text());
    if(query.exec()){
        if(query.size() > 0){
            QMessageBox::warning(this,"警告","奶山羊编号重复!");
            return false;
        }else{
            return true;
        }
    }else{
        QMessageBox::warning(this,"警告","数据库未登录!");
        return false;
    }
}

void AddGoatDialog::on_confirmButton_clicked()
{
    if(!checkGoatId()){
        return;
    }
    bool ok = false;
    float weight = ui->weightLineEdit->text().toFloat(&ok);
    if(ok){
        QSqlQuery query;
        query.prepare("insert into goatInfo(goatId,weight,houseId,inTime) values(:goatId,:weight,:houseId,now());");
        query.bindValue(":houseId",ui->houseIdComboBox->currentText());
        query.bindValue(":goatId",ui->goatIdLineEdit->text());
        query.bindValue(":weight",weight);
        if(query.exec()){
            QMessageBox::information(this,"成功","添加奶山羊成功!");
            this->hide();
        }else{
            qDebug() << query.lastQuery();
              QSqlError err;
            err= query.lastError();
             qDebug() << err.text();
            QMessageBox::warning(this,"警告","添加奶山羊失败!");
        }
    }else{
        QMessageBox::warning(this,"警告","体重非法!");
    }

}
