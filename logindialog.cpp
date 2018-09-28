#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if(DB::instance().data()->setDb(ui->serverUser->text().trimmed(),ui->serverPassword->text(),ui->serverIp->text().trimmed())){
        emit loginSignal();
        QMessageBox::information(this,"登录","登录成功!");
        this->hide();
    }else{
        QMessageBox::warning(this,"警告","登录失败!");
    }
}
