#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();
public slots:
    void aboutUser();
    void aboutSport();
    void aboutInfo();
    void aboutSetting();
    void aboutUs();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
