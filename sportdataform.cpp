#include "sportdataform.h"
#include "ui_sportdataform.h"

SportDataForm::SportDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SportDataForm)
{
    ui->setupUi(this);
//    setContextMenuPolicy(Qt::DefaultContextMenu);
//    connect(ui->tabWidget,SIGNAL(tabBarDoubleClicked(int)),this,SLOT(delete_tab()));
    ui->tabWidget->setTabsClosable(true);
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(delete_tab(int)));
}

SportDataForm::~SportDataForm()
{
    delete ui;
}

void SportDataForm::updateTabs(){
    //MainForm* curTab = (MainForm*)ui->tabWidget->currentWidget();
    QString curTabLabel;
    bool memoryFlag = false;
    if(ui->tabWidget->count() > 0){
        memoryFlag = true;
        curTabLabel = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
        ui->tabWidget->clear();
    }
    QSqlQuery query;
    query.exec("select * from houseInfo;");
    while(query.next()){
        InformationForm *temp = new InformationForm();
        //MainForm *temp = new MainForm();
        temp->setHouseId(query.value(0).toString());
        connect(this,SIGNAL(updateSignal()),temp,SLOT(updateGoatList()));
        ui->tabWidget->addTab(temp,QIcon(":/nu.png"),query.value(0).toString());
    }
    if(memoryFlag){
        for(int i = 0; i < ui->tabWidget->count();i++){
            if(curTabLabel == ui->tabWidget->tabText(i)){
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
    emit updateSignal();
}

void SportDataForm::on_pushButton_clicked()
{
    insert_tab();
}


void SportDataForm::on_pushButton_2_clicked()
{
    delete_tab();
}

void SportDataForm::delete_tab(int index){
    ui->tabWidget->removeTab(index);
}

void SportDataForm::insert_tab(){
    //MainForm *temp = new MainForm();
    InformationForm *temp = new InformationForm();
//    ui->tabWidget->addTab(temp,"舍?");
//    QIcon icon;
//    icon.addFile(tr(":/nu.png"));
    ui->tabWidget->addTab(temp,QIcon(":/nu.png"),QString("舍?"));
}

void SportDataForm::delete_tab(){
    ui->tabWidget->removeTab(ui->tabWidget->count() - 1);
}

//void SportDataForm::delete_current_index(){

//}

//void SportDataForm::contextMenuEvent(QContextMenuEvent *event){
//    qDebug() << event->x();
//    QMenu *menu = new QMenu(this);
//    QAction *action_delete_this = new QAction(tr("&Delete"),menu);
//    menu->addAction(new QAction(tr("&Del"),menu));
//    menu->move(cursor().pos());
//    menu->show();
//}
