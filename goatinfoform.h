#ifndef GOATINFOFORM_H
#define GOATINFOFORM_H

#include <QWidget>

namespace Ui {
class GoatInfoForm;
}

class GoatInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit GoatInfoForm(QWidget *parent = 0);
    ~GoatInfoForm();

private:
    Ui::GoatInfoForm *ui;
};

#endif // GOATINFOFORM_H
