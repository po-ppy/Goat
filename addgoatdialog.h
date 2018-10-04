#ifndef ADDGOATDIALOG_H
#define ADDGOATDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

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
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AddGoatDialog *ui;
};

#endif // ADDGOATDIALOG_H
