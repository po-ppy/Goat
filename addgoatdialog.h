#ifndef ADDGOATDIALOG_H
#define ADDGOATDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class AddGoatDialog;
}

class AddGoatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGoatDialog(QWidget *parent = 0);
    ~AddGoatDialog();
public slots:
    bool checkDB();
    QString createGoatId();
    void loadHouseId();
    void onShowOut();
    bool checkGoatId();
private slots:
    void on_pushButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::AddGoatDialog *ui;
};

#endif // ADDGOATDIALOG_H
