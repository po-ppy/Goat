#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    ui->tableView->resizeColumnsToContents();
    createChart();
}

InformationForm::~InformationForm()
{
    delete ui;
}

void InformationForm::createChart(){
    chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("运动数据曲线");



    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis;
    axisY->setMax(40);
    axisY->setMin(-20);
    //axisY->setLinePenColor(series->pen().color());

    chart->addAxis(axisY, Qt::AlignLeft);



    linex = new QSplineSeries;
    liney = new QSplineSeries;
    linez = new QSplineSeries;

    scatterx = new QScatterSeries;
    scattery = new QScatterSeries;
    scatterz = new QScatterSeries;

    chart->addSeries(linex);
    chart->addSeries(liney);
    chart->addSeries(linez);

    chart->addSeries(scatterx);
    chart->addSeries(scattery);
    chart->addSeries(scatterz);


    linex->attachAxis(axisX);
    linex->attachAxis(axisY);
    liney->attachAxis(axisX);
    liney->attachAxis(axisY);
    linez->attachAxis(axisX);
    linez->attachAxis(axisY);

    scatterx->attachAxis(axisX);
    scatterx->attachAxis(axisY);
    scattery->attachAxis(axisX);
    scattery->attachAxis(axisY);
    scatterz->attachAxis(axisX);
    scatterz->attachAxis(axisY);

    linex->setName("line:x");
    liney->setName("line:y");
    linez->setName("line:z");

    scatterx->setName("point:x");
    scattery->setName("point:y");
    scatterz->setName("point:z");

    scatterx->setColor(linex->color());
    scattery->setColor(liney->color());
    scatterz->setColor(linez->color());

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    ui->gridLayout->addWidget(chartView);
}

void InformationForm::setHouseId(QString inHouseId){
    houseId = inHouseId;
}

QString InformationForm::getHouseId(){
    return houseId;
}

void InformationForm::updateGoatList(){
    QSqlQuery query;
   // query.prepare("select goatId as 山羊编号, shehao as 舍号, deviceId as 绑定设备id, weight as 体重, inTime as 入圈时间, outTime as 出圈时间 from goatInfo where shehao = :shehao;");
    query.prepare("select goatId as 奶山羊编号, status as 运动状态 from tempView where houseId = :houseId;");
    query.bindValue(":houseId",houseId);
    query.exec();
    sqlQueryModel->setQuery(query);

    sortFilterProxyModel->setDynamicSortFilter(true);
    sortFilterProxyModel->setSourceModel(sqlQueryModel);

    ui->tableView->setModel(sortFilterProxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
