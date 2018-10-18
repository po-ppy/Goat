#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginDialog = new LoginDialog(this);
    helpDialog = new HelpDialog(this);

    sportDataForm = new SportDataForm(this);
    goatQueryForm = new GoatQueryForm(this);
    deviceQueryForm = new DeviceQueryForm(this);

    bdDialog = new bindingDialog(this);

    ui->stackedWidget->addWidget(sportDataForm);
    ui->stackedWidget->addWidget(goatQueryForm);
    ui->stackedWidget->addWidget(deviceQueryForm);

    this->setWindowTitle("奶山羊行为检测与信息管理系统");

    ui->stackedWidget->setCurrentWidget(sportDataForm);

    connect(ui->actionD,SIGNAL(triggered(bool)),this,SLOT(change_to_goat_query_form()));
    connect(ui->action_3,SIGNAL(triggered(bool)),this,SLOT(change_to_sport_data_form()));
    connect(ui->action_Device_Query,SIGNAL(triggered(bool)),this,SLOT(change_to_device_query_form()));
    connect(ui->action,SIGNAL(triggered(bool)),bdDialog,SLOT(show()));

    connect(goatQueryForm,SIGNAL(updateSignal()),this,SLOT(updateAllTables()));
    connect(deviceQueryForm,SIGNAL(updateSignal()),this,SLOT(updateAllTables()));
    connect(bdDialog,SIGNAL(updateSignal()),this,SLOT(updateAllTables()));
    //connect(ui->action_2,SIGNAL(triggered(bool)),this,SLOT(change_to_sport_data_form()));

    connect(goatQueryForm,SIGNAL(goatIdSignal(QString)),bdDialog,SLOT(receiveGoatId(QString)));
    connect(deviceQueryForm,SIGNAL(deviceIdSignal(QString)),bdDialog,SLOT(receiveDeviceId(QString)));

    connect(ui->actionLogin,SIGNAL(triggered(bool)),loginDialog,SLOT(show()));
    connect(loginDialog,SIGNAL(loginSignal()),this,SLOT(loginOK()));
    connect(ui->actionLogout,SIGNAL(triggered(bool)),this,SLOT(doLogout()));
    connect(ui->actionHelp,SIGNAL(triggered(bool)),helpDialog,SLOT(show()));
    setWindowIcon(QIcon(":/nu.ico"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_to_goat_query_form(){
    ui->stackedWidget->setCurrentWidget(goatQueryForm);
}

void MainWindow::change_to_sport_data_form(){
    ui->stackedWidget->setCurrentWidget(sportDataForm);
}

void MainWindow::change_to_device_query_form(){
    ui->stackedWidget->setCurrentWidget(deviceQueryForm);
}

void MainWindow::updateAllTables(){
    goatQueryForm->refreshView();
    deviceQueryForm->refreshView();
    bdDialog->updateGoatTable();
    bdDialog->updateDeviceTable();
    sportDataForm->updateTabs();
}

void MainWindow::loginOK(){
    ui->actionLogin->setText("已登录");
    ui->actionLogin->setDisabled(true);
    updateAllTables();
}

void MainWindow::doLogout(){
    DB::instance().data()->getDb().close();
    ui->actionLogin->setText("登录");
    ui->actionLogin->setEnabled(true);
}
