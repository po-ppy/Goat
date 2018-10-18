#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bindingdialog.h>
#include <sportdataform.h>
#include <goatqueryform.h>
#include <devicequeryform.h>
#include <logindialog.h>
#include <helpdialog.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateAllTables();
    void loginOK();
    void doLogout();
private slots:
    void change_to_goat_query_form();
    void change_to_sport_data_form();
    void change_to_device_query_form();
private:
    Ui::MainWindow *ui;
    SportDataForm *sportDataForm;
    GoatQueryForm *goatQueryForm;
    DeviceQueryForm *deviceQueryForm;
    bindingDialog *bdDialog;
    LoginDialog *loginDialog;
    HelpDialog *helpDialog;
};

#endif // MAINWINDOW_H
