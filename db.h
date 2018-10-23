#ifndef DB_H
#define DB_H
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlQuery>

class DB
{
public:
    static QSharedPointer<DB>& instance(){
        if (m_pInstance.isNull())
                {
                    QMutexLocker mutexLocker(&m_Mutex);
                    if (m_pInstance.isNull())
                        m_pInstance = QSharedPointer<DB>(new DB());
                }
                return m_pInstance;
    }
    QSqlDatabase& getDb();
    bool setDb(QString userName, QString userPwd, QString userIp);

private:
    DB();
    DB(const DB&);
    DB& operator ==(const DB&);
private:
    QSqlDatabase db;
    static QMutex m_Mutex;
    static QSharedPointer<DB> m_pInstance;

};


#endif // DB_H
