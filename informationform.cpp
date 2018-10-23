#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    freshTimer = new QTimer(this);
    sqlQueryModel = new QSqlQueryModel(this);
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    ui->tableView->resizeColumnsToContents();
    createChart();

    connect(freshTimer,SIGNAL(timeout()),this,SLOT(updateAllData()));
    freshTimer->start(1000);
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
    axisY->setMax(25);
    axisY->setMin(-15);
    //axisY->setLinePenColor(series->pen().color());

    chart->addAxis(axisY, Qt::AlignLeft);



    linex = new QSplineSeries;
    liney = new QSplineSeries;
    linez = new QSplineSeries;
    lineg = new QSplineSeries;

    //scatterx = new QScatterSeries;
    //scattery = new QScatterSeries;
    //scatterz = new QScatterSeries;
    scatterg = new QScatterSeries;

    chart->addSeries(linex);
    chart->addSeries(liney);
    chart->addSeries(linez);
    chart->addSeries(lineg);

    //chart->addSeries(scatterx);
    //chart->addSeries(scattery);
    //chart->addSeries(scatterz);
    chart->addSeries(scatterg);


    linex->attachAxis(axisX);
    linex->attachAxis(axisY);
    liney->attachAxis(axisX);
    liney->attachAxis(axisY);
    linez->attachAxis(axisX);
    linez->attachAxis(axisY);
    lineg->attachAxis(axisX);
    lineg->attachAxis(axisY);

    //scatterx->attachAxis(axisX);
    //scatterx->attachAxis(axisY);
    //scattery->attachAxis(axisX);
    //scattery->attachAxis(axisY);
    //scatterz->attachAxis(axisX);
    //scatterz->attachAxis(axisY);
    scatterg->attachAxis(axisX);
    scatterg->attachAxis(axisY);

    linex->setName("line:x");
    liney->setName("line:y");
    linez->setName("line:z");
    lineg->setName("合加速度:g");

    //scatterx->setName("point:x");
    //scattery->setName("point:y");
    //scatterz->setName("point:z");
    scatterg->setName("point:g");

    lineg->setColor(QColor("black"));
    //scatterx->setColor(linex->color());
    //scattery->setColor(liney->color());
    //scatterz->setColor(linez->color());
    scatterg->setColor(lineg->color());

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

void InformationForm::updateAllData(){
    if(this->isVisible()){
        updateGoatList();
        updateHouseData();
        updateChart();
    }
}

void InformationForm::updateGoatList(){
    QSqlQuery query;
   // query.prepare("select goatId as 山羊编号, shehao as 舍号, deviceId as 绑定设备id, weight as 体重, inTime as 入圈时间, outTime as 出圈时间 from goatInfo where shehao = :shehao;");
    query.prepare("select goatId as 奶山羊编号,status as 运动状态 from sportDataView where houseId = :houseId;");
    query.bindValue(":houseId",houseId);
    if(query.exec()){
        //qDebug() << houseId;
        sqlQueryModel->setQuery(query);

        sortFilterProxyModel->setDynamicSortFilter(true);
        sortFilterProxyModel->setSourceModel(sqlQueryModel);

        ui->tableView->setModel(sortFilterProxyModel);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->horizontalHeader()->setSortIndicator(0,Qt::AscendingOrder);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);

        autoShow();
    }else{
        qDebug() << "goatList error";
    }

}

void InformationForm::updateHouseData(){
    QSqlQuery query;
    query.prepare("select * from houseDataView where houseId = :houseId;");
    query.bindValue(":houseId",houseId);

    if(query.exec()){
       // qDebug() << query.size();
        if(query.next()){
            //qDebug() << houseId;
            this->ui->datatijmeLabel->setText(QDateTime::fromMSecsSinceEpoch(query.value("datatimem").toLongLong()).toString("yyyy-MM-dd hh:mm:ss:zzz"));
            this->ui->wenduLabel->setText(query.value("wendu").toString());
            //this->ui->shiduLabel->setText(query.value("shidu").toString());
            //this->ui->eryangLabel->setText(query.value("eryang").toString());
            this->ui->anqiLabel->setText(query.value("anqi").toString());
            this->ui->shiduLabel->setText("51.4");
            this->ui->eryangLabel->setText("537.2");
        }
    }
}

void InformationForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    selectOne(index.row(),0);
}


void InformationForm::updateChart(){
    if(ui->deviceIdLabel->text() != "" && ui->goatIdLabel->text() != ""){
        QSqlQuery query;
        //query.prepare("select * from (select * from sportData where goatId = :goatId ORDER By datatimem desc limit 10) aa order by id;");
        query.prepare("select * from sportData where goatId = :goatId ORDER By datatimem desc limit 10;");
        query.bindValue(":goatId",ui->goatIdLabel->text());
        if(query.exec()){
            if(query.size() == 0){
                qDebug() << "size == 0";
                return;
            }
            //qDebug() << houseId;
            datax.clear();
            datay.clear();
            dataz.clear();
            datag.clear();

            while(query.next()){
                datax.push_front(QPointF(query.value("datatimem").toLongLong(),toG(query.value("sportx").toLongLong())));
                datay.push_front(QPointF(query.value("datatimem").toLongLong(),toG(query.value("sporty").toLongLong())));
                dataz.push_front(QPointF(query.value("datatimem").toLongLong(),toG(query.value("sportz").toLongLong())));
                datag.push_front(QPointF(query.value("datatimem").toLongLong(),getG(query.value("sportx").toLongLong(),query.value("sporty").toLongLong(),query.value("sportz").toLongLong())));
            }
            //qDebug() << datag.last().ry();
            //qDebug() << QDateTime::fromMSecsSinceEpoch(datax.first().rx()).toMSecsSinceEpoch();
            //qDebug() << QDateTime::fromMSecsSinceEpoch(datax.last().rx()).toMSecsSinceEpoch();

            linex->replace(datax);
            liney->replace(datay);
            linez->replace(dataz);
            lineg->replace(datag);

            //scatterx->replace(datax);
            //scattery->replace(datay);
            //scatterz->replace(dataz);
            scatterg->replace(datag);

            axisX->setMax(QDateTime::fromMSecsSinceEpoch(datax.last().rx()));
            axisX->setMin(QDateTime::fromMSecsSinceEpoch(datax.first().rx()));
        }else{
            qDebug() << "图表查询失败";
        }
    }
}

double InformationForm::toG(double in){
    //qDebug() << (in/17884)*9.8 << "  ggg";
    return (in/17884)*9.8;
}

double InformationForm::toG(QByteArray in){
    //qDebug() << (in.toLongLong()/16884)*9.8 << "  ggg";
    return (in.toLongLong()/17884)*9.8;
}

double InformationForm::getG(double in1, double in2, double in3){
    qDebug() << toG(sqrt(in1*in1+in2*in2+in3*in3)) << "  ggg";
    return toG(sqrt(in1*in1+in2*in2+in3*in3));
}

void InformationForm::autoShow(){
    if(ui->goatIdLabel->text() == ""){
        selectOne(0,0);
    }
}

void InformationForm::selectOne(int row, int col){
    QString tempGoatId = ui->tableView->model()->index(row,col).data().toString();
    ui->goatIdLabel->setText(tempGoatId);
    ui->deviceIdLabel->setText("");
    QSqlQuery query;
    query.prepare("select deviceId from bindingInfo where goatId = :goatId;");
    query.bindValue(":goatId",tempGoatId);
    if(query.exec()){
        if(query.next()){
            ui->deviceIdLabel->setText(query.value("deviceId").toString());
        }
    }
}
