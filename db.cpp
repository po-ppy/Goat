#include "db.h"

QMutex DB::m_Mutex;
QSharedPointer<DB> DB::m_pInstance;

DB::DB()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    //db.addDatabase("QMYSQL");
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("root");
    db.setDatabaseName("goatdb");
    //db.open();
}

QSqlDatabase& DB::getDb(){
    return db;
}

bool DB::setDb(QString userName, QString userPwd, QString userIp){
    if(db.isOpen()){
        db.close();
    }
    db.setDatabaseName("goatdb");
    db.setHostName(userIp);
    db.setUserName(userName);
    db.setPassword(userPwd);
    return db.open();
}
