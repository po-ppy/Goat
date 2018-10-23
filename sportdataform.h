#ifndef SPORTDATAFORM_H
#define SPORTDATAFORM_H

#include <QWidget>
//#include <mainform.h>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QContextMenuEvent>
#include <QIcon>
#include <QSqlQuery>
#include <QThread>
#include <informationform.h>



namespace Ui {
class SportDataForm;
}

class SportDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit SportDataForm(QWidget *parent = 0);
    ~SportDataForm();
signals:
    void updateSignal();
public slots:
    void updateTabs();
private slots:
    void insert_tab();
    void delete_tab();
    void delete_tab(int index);
//    void contextMenuEvent(QContextMenuEvent *event);
//    void delete_current_index();
private:
    Ui::SportDataForm *ui;
    //QThread *wkThread;

};

#endif // SPORTDATAFORM_H
