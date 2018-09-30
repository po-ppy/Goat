#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
public slots:
    void setHouseId(QString inHouseId);
    QString getHouseId();

private:
    Ui::MainForm *ui;
    QString houseId;
};

#endif // MAINFORM_H
