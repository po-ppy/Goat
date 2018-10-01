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
#include <QDateTime>
#include <QTimer>
#include <QByteArray>
#include <QPointF>
#include <QDebug>
#include <QtMath>
#include <QModelIndex>

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
    void updateAllData();
    void updateGoatList();
    void updateHouseData();
    void updateChart();
    double toG(double in);
    double toG(QByteArray in);
    double getG(double in1,double in2,double in3);
    void autoShow();
    void selectOne(int row,int col);
private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::InformationForm *ui;

    QString houseId;

    QTimer *freshTimer;

    QSqlQueryModel *sqlQueryModel;
    QSortFilterProxyModel *sortFilterProxyModel;

    QChart *chart;
    QChartView *chartView;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QSplineSeries *linex;
    QSplineSeries *liney;
    QSplineSeries *linez;
    QSplineSeries *lineg;

    //QScatterSeries *scatterx;
    //QScatterSeries *scattery;
    //QScatterSeries *scatterz;
    QScatterSeries *scatterg;

    QList<QPointF> datax ;
    QList<QPointF> datay ;
    QList<QPointF> dataz ;
    QList<QPointF> datag ;
};

#endif // INFORMATIONFORM_H
