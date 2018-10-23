#include "goatinfoform.h"
#include "ui_goatinfoform.h"

GoatInfoForm::GoatInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoatInfoForm)
{
    ui->setupUi(this);
}

GoatInfoForm::~GoatInfoForm()
{
    delete ui;
}

