#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sportDataForm = new SportDataForm(this);
    goatQueryForm = new GoatQueryForm(this);
    deviceQueryForm = new DeviceQueryForm(this);

    ui->stackedWidget->addWidget(sportDataForm);
    ui->stackedWidget->addWidget(goatQueryForm);
    ui->stackedWidget->addWidget(deviceQueryForm);

    this->setWindowTitle("奶山羊行为检测与信息管理系统");

    ui->stackedWidget->setCurrentWidget(sportDataForm);

    connect(ui->actionD,SIGNAL(triggered(bool)),this,SLOT(change_to_goat_query_form()));
    connect(ui->action_3,SIGNAL(triggered(bool)),this,SLOT(change_to_sport_data_form()));
    connect(ui->action_Device_Query,SIGNAL(triggered(bool)),this,SLOT(change_to_device_query_form()));
    //connect(ui->action_2,SIGNAL(triggered(bool)),this,SLOT(change_to_sport_data_form()));

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
