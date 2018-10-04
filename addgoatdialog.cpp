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

void AddGoatDialog::on_pushButton_4_clicked()
{
    ui->houseIdComboBox->setEnabled(!ui->houseIdComboBox->isEnabled());
}

void AddGoatDialog::onShowOut(){
    if(checkDB()){
        ui->goatIdLineEdit->setText(createGoatId());
        loadHouseId();
    }else{
        ui->goatIdLineEdit->setText("请先登录");
    }
}
