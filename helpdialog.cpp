#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::aboutUser(){
    ui->textEdit->clear();
    //ui->textEdit->setFont(QFont("Sans Serif",16,20));
    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setFontWeight(20);
    ui->textEdit->append("用户");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->append("");
    ui->textEdit->append("使用mysql数据库账号和密码进行登录。");
    ui->textEdit->append("");
    ui->textEdit->append("数据库中需要有goatdb数据库，否则请从数据处理程序(GoatDataServer)初始化数据库再使用。");
}

void HelpDialog::aboutSport(){
    ui->textEdit->clear();
    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setFontWeight(20);
    ui->textEdit->append("运动监测");
    ui->textEdit->append("");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->append("显示各羊舍的环境数据和其中奶山羊的运动状态。");
    ui->textEdit->append("");

}


void HelpDialog::aboutInfo(){
    ui->textEdit->clear();
    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setFontWeight(20);
    ui->textEdit->append("信息管理");
    ui->textEdit->append("");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->append("奶山羊信息管理：管理羊舍、奶山羊信息，右键菜单可用，可添加、删除羊舍，解绑、转移、删除奶山羊，报告设备故障，导出奶山羊信息，导入奶山羊信息。");
    ui->textEdit->append("");
    ui->textEdit->append("设备信息管理：管理设备信息，右键菜单可用，可执行解绑、报告故障、恢复使用、删除等操作。");
    ui->textEdit->append("");
    ui->textEdit->append("设备无需手动导入，系统正常运行，终端上电即可自动添加。");
}

void HelpDialog::aboutSetting(){
    ui->textEdit->clear();
    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setFontWeight(20);
    ui->textEdit->append("设置");
    ui->textEdit->append("");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->append("绑定设置，建议单击‘双击绑定’，可快速绑定，‘双击绑定’可用则‘确认绑定’不可用，再次单击可以使用‘确认绑定’。");
    ui->textEdit->append("");
    ui->textEdit->append("文件导入可以快速导入绑定信息，需要数据库中有对应的奶山羊信息和设备信息。");
}

void HelpDialog::aboutUs(){
    ui->textEdit->clear();
    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setFontWeight(20);
    ui->textEdit->append("关于我们");
    ui->textEdit->append("");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->append("奶山羊信息管理系统");
    ui->textEdit->append("");
    ui->textEdit->append("西农科创团队");
}

void HelpDialog::on_listWidget_clicked(const QModelIndex &index)
{
    switch (index.row()) {
    case 0:
        aboutUser();
        break;
    case 1:
        aboutSport();
        break;
    case 2:
        aboutInfo();
        break;
    case 3:
        aboutSetting();
        break;
    case 4:
        aboutUs();
        break;
    default:
        break;
    }
}
