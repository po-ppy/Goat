#ifndef BINDINGDIALOG_H
#define BINDINGDIALOG_H

#include <QDialog>
#include <db.h>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>

namespace Ui {
class bindingDialog;
}

class bindingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bindingDialog(QWidget *parent = 0);
    ~bindingDialog();

private:
    Ui::bindingDialog *ui;
};

#endif // BINDINGDIALOG_H
