#ifndef DEVICEQUERYFORM_H
#define DEVICEQUERYFORM_H

#include <QWidget>
#include <db.h>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class DeviceQueryForm;
}

class DeviceQueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceQueryForm(QWidget *parent = 0);
    ~DeviceQueryForm();
public slots:
    void updateTableWidgest();
    void showAllData();
    void updateTableWidgestByState();
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

private:
    Ui::DeviceQueryForm *ui;
    QSqlQueryModel *sqlQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;
};

#endif // DEVICEQUERYFORM_H