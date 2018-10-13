#ifndef BINDINGDIALOG_H
#define BINDINGDIALOG_H

#include <QDialog>
#include <db.h>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>

namespace Ui {
class bindingDialog;
}

class bindingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bindingDialog(QWidget *parent = 0);
    ~bindingDialog();
signals:
    void updateSignal();
private:
    Ui::bindingDialog *ui;
    QSqlQueryModel *goatSqlQueryModel;
    QSortFilterProxyModel *goatSortFilterProxyModel;
    QSqlQueryModel *deviceSqlQueryModel;
    QSortFilterProxyModel *deviceSortFilterProxyModel;
   // QSqlQuery *qSqlQuery;
public slots:
    void updateGoatTable();
    void updateDeviceTable();
    void startBinding();
    void receiveGoatId(QString goatId);
    void receiveDeviceId(QString deviceId);
    void addFromFile();
private slots:
    void on_goatCheckBox_stateChanged(int arg1);
    void on_deviceCheckBox_stateChanged(int arg1);
    void on_doubleButton_clicked();
    void on_goatTableView_doubleClicked(const QModelIndex &index);
    void on_deviceTableView_doubleClicked(const QModelIndex &index);
    void on_confirmButton_clicked();
    void on_selectFileButton_clicked();
};

#endif // BINDINGDIALOG_H
