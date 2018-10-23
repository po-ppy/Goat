#ifndef DEVICEQUERYFORM_H
#define DEVICEQUERYFORM_H

#include <QWidget>
#include <db.h>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDateTime>
#include <QModelIndexList>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class DeviceQueryForm;
}

class DeviceQueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceQueryForm(QWidget *parent = 0);
    ~DeviceQueryForm();
signals:
    void updateSignal();
    void deviceIdSignal(QString);
public slots:
    void updateTableWidgest();
    void showAllData();
    void updateTableWidgestByState();
    void bindSelected();
    void unbindSelected();
    void errorSelected();
    void restartSelected();
    void deleteSelected();
    void refreshView();
    void updateHouseId();
    void exportSelected();
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_tableView_customContextMenuRequested(const QPoint &pos);


private:
    Ui::DeviceQueryForm *ui;
    QSqlQueryModel *sqlQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;
    QMenu *cmenu;
    QAction *actionR1;
    QAction *actionR2;
    QAction *actionR3;
    QAction *actionR4;
    QAction *actionR5;
    QAction *actionR6;
    int refreshFlag;
};

#endif // DEVICEQUERYFORM_H
