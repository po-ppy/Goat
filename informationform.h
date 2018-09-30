#ifndef INFORMATIONFORM_H
#define INFORMATIONFORM_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class InformationForm;
}

class InformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit InformationForm(QWidget *parent = 0);
    ~InformationForm();
public slots:
    void createChart();
    void setHouseId(QString inHouseId);
    QString getHouseId();
    void updateGoatList();
private:
    Ui::InformationForm *ui;

    QString houseId;

    QSqlQueryModel *sqlQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;

    QChart *chart;
    QChartView *chartView;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QSplineSeries *linex;
    QSplineSeries *liney;
    QSplineSeries *linez;

    QScatterSeries *scatterx;
    QScatterSeries *scattery;
    QScatterSeries *scatterz;

    QList<QPointF> datax ;
    QList<QPointF> datay ;
    QList<QPointF> dataz ;
};

#endif // INFORMATIONFORM_H
