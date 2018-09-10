#ifndef SPORTDATAFORM_H
#define SPORTDATAFORM_H

#include <QWidget>
#include <mainform.h>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QContextMenuEvent>
#include <QIcon>

namespace Ui {
class SportDataForm;
}

class SportDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit SportDataForm(QWidget *parent = 0);
    ~SportDataForm();

private slots:
    void insert_tab();
    void delete_tab();
    void delete_tab(int index);
//    void contextMenuEvent(QContextMenuEvent *event);
//    void delete_current_index();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SportDataForm *ui;

};

#endif // SPORTDATAFORM_H
