#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setHouseId(QString inHouseId){
    houseId = inHouseId;
}

QString MainForm::getHouseId(){
    return houseId;
}
