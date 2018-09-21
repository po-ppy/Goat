#ifndef CHANGEGOATINFODIALOG_H
#define CHANGEGOATINFODIALOG_H

#include <QDialog>
#include <QList>
#include <QDebug>
#include <QDateTime>
#include <QClipboard>
#include <db.h>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class ChangeGoatInfoDialog;
}

class ChangeGoatInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeGoatInfoDialog(QWidget *parent = 0);
    ~ChangeGoatInfoDialog();
public slots:
    bool fillData(QList<QString> tempList);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

signals:
    void refresh_table();
private:
    Ui::ChangeGoatInfoDialog *ui;
    QClipboard *board;
    QList<QString> list;
};

#endif // CHANGEGOATINFODIALOG_H
