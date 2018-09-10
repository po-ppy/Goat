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
    MainForm *temp = new MainForm();
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
