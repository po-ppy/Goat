#include "bindingdialog.h"
#include "ui_bindingdialog.h"

bindingDialog::bindingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bindingDialog)
{
    ui->setupUi(this);
}

bindingDialog::~bindingDialog()
{
    delete ui;
}
