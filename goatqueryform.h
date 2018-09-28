#ifndef GOATQUERYFORM_H
#define GOATQUERYFORM_H

#include <QWidget>
#include <db.h>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDateTime>
#include <QModelIndexList>
#include <QList>
#include <changegoatinfodialog.h>
#include <QMenu>
#include <QAction>

namespace Ui {
class GoatQueryForm;
}

class GoatQueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit GoatQueryForm(QWidget *parent = 0);
    ~GoatQueryForm();
    //void goatQueryHeaderModelInit();
public slots:
    void updateTableWidgest();
    void showAllData();
    void deleteSelected();
    void unbindSelected();
    void bindSelected();
    void errorSelected();
    void refreshView();
    void updateHouseId();
signals:
    void updateSignal();
    void goatIdSignal(QString);

private slots:
    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::GoatQueryForm *ui;
    QSqlQueryModel *sqlQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;
    ChangeGoatInfoDialog *changeDialog;
    QMenu *cmenu;
    QAction *actionR1;
    QAction *actionR2;
    QAction *actionR3;
    QAction *actionR4;
    int refreshFlag;
//    QStandardItemModel *headerModel;
};

#endif // GOATQUERYFORM_H
