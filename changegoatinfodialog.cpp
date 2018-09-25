
#include "changegoatinfodialog.h"
#include "ui_changegoatinfodialog.h"

ChangeGoatInfoDialog::ChangeGoatInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeGoatInfoDialog)
{
    ui->setupUi(this);
    board = QApplication::clipboard();
}

ChangeGoatInfoDialog::~ChangeGoatInfoDialog()
{
    delete ui;
}

bool ChangeGoatInfoDialog::fillData(QList<QString> tempList){
    this->list = tempList;
    if(this->list.size() < 6){
        return false;
    }else{
        for(int i = 0;i < 6;i++){
            switch(i){
            case 0:
                ui->lineEdit->setText(list.at(i));
                break;
            case 1:
                ui->lineEdit_3->setText(list.at(i));
                break;
            case 2:
                ui->lineEdit_4->setText(list.at(i));
                break;
            case 3:
                ui->lineEdit_5->setText(list.at(i));
                break;
            case 4:
                //QDateTime temp = QDateTime::fromString(list.at(i));
                ui->dateTimeEdit->setDateTime(QDateTime::fromString(list.at(i),Qt::ISODate));
                break;
            case 5:
                ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(list.at(i),Qt::ISODate));
                break;;
            default:
                qDebug() << "WTF?????";
                break;
            }
        }
    }
}

void ChangeGoatInfoDialog::on_pushButton_2_clicked()
{
    QString str = "";
    for(int i = 0;i < list.size();i++){
        switch(i){
        case 0:
            str += "奶山羊编号："+list.at(i) +"\n";
            break;
        case 1:
            str += "绑定设备编号："+list.at(i) +"\n";
            break;
        case 2:
            str += "舍号："+list.at(i) +"\n";
            break;
        case 3:
            str += "体重："+list.at(i) + "\n";
            break;
        case 4:
           str += "入圈时间："+QDateTime::fromString(list.at(i),Qt::ISODate).toString("yyyy-MM-dd hh:mm:ss") +"\n";
            break;
        case 5:
            str += "出圈时间："+QDateTime::fromString(list.at(i),Qt::ISODate).toString("yyyy-MM-dd hh:mm:ss")+"\n";
            break;;
        default:
            qDebug() << "WTF?????";
            break;
        }
    }
    board->setText(str);
}

void ChangeGoatInfoDialog::on_pushButton_clicked()
{
    QSqlQuery query(DB::instance().data()->getDb());
    query.prepare("update goatInfo set houseId = :houseId,weight = :weight,inTime = :inTime,outTime = :outTime where goatId = :goatId;");
    query.bindValue(":goatId",ui->lineEdit->text());
    query.bindValue(":houseId",ui->lineEdit_4->text());
    query.bindValue(":weight",ui->lineEdit_5->text());
    query.bindValue(":inTime",ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":outTime",ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(query.exec()){
        QMessageBox::information(this,"修改结果","修改成功！");
        emit refresh_table();
        this->close();
    }else{
        QMessageBox::warning(this,"修改结果","修改失败！");
        qDebug() << query.lastError().databaseText();
    }
}

void ChangeGoatInfoDialog::on_pushButton_3_clicked()
{

}
