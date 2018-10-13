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
#include <addgoatdialog.h>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QFileDialog>
#pragma execution_character_set("utf-8")

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
    void addHouseId();
    void deleteHouseId();
    void renameHouseId();
    void addMoreHouseId();
    void moveToHouse();
    void showNoHouseGoat();
    void addGoat();
    void addFromFile();
    void exportToFile();
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

    void on_houseIdTableView_customContextMenuRequested(const QPoint &pos);

    void on_addNewHosueButton_clicked();

    void on_addGoatButton_clicked();

    void on_addFromFileButton_clicked();

    void on_exportButton_clicked();

private:
    Ui::GoatQueryForm *ui;
    QSqlQueryModel *sqlQueryModel;
    QSqlQueryModel *houseQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;
    ChangeGoatInfoDialog *changeDialog;
    AddGoatDialog *addGoatDialog;
    QMenu *cmenu;
    QAction *actionR1;
    QAction *actionR2;
    QAction *actionR3;
    QAction *actionR4;
    QAction *actionMoveToHouse;
    QAction *actionExport;
    QMenu *houseMenu;
    QAction *actionRenameHouse;
    QAction *actionDeleteHouse;
    QAction *actionAddHouse;
    int refreshFlag;
//    QStandardItemModel *headerModel;
};

#endif // GOATQUERYFORM_H
