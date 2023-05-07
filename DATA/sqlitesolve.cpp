#include "sqlitesolve.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>


QMutex SQLiteSolve::s_mutex;
SQLiteSolve* SQLiteSolve::s_sqliteSolve = nullptr;

SQLiteSolve& SQLiteSolve::instance() {
    if (!s_sqliteSolve) {
        QMutexLocker locker(&s_mutex);
        if (!s_sqliteSolve) {
            s_sqliteSolve = new SQLiteSolve;
        }
    }
    return *s_sqliteSolve;
}

SQLiteSolve::SQLiteSolve() {
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("sqliteDemo.db");
    if (!m_database.open()) {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    } else {
        qDebug() << "Successed to connect database." << m_database.lastError();
    }
}

SQLiteSolve::~SQLiteSolve() {
    m_database.close();
}

QSqlDatabase& SQLiteSolve::getDatabase() {
    return m_database;
}

bool SQLiteSolve::executeSql(const QString& sql) {
    QSqlQuery query(m_database);
    if (!query.exec(sql)) {
        qDebug() << "Error: Failed to execute sql." << query.lastError();
        return false;
    } else {
        qDebug() << "Successed to execute sql." << sql;
        return true;
    }
}

bool SQLiteSolve::addRecord(const QString& tableName, const QString& values) {
QStringList valueList = values.split("|"); // 将传入的values字符串按照“|”分割成字符串列表
QString sql = QString("INSERT INTO %1 VALUES (").arg(tableName);
for (int i = 0; i < valueList.size(); i++) {
if (i != 0) {
sql += ",";
}
sql +=  valueList.at(i) ;
}
sql += ");";
// qDebug()<<"NOW:"<<sql<<endl;
return executeSql(sql);
}
// 示例：
// SQLiteSolve::instance().addRecord("student", "'Alice'|18|'女'");
// SQLiteSolve::instance().addRecord("student", "'Bob'|20|'男'");
// SQLiteSolve::instance().addRecord("student", "'Tom'|21|'男'");

bool SQLiteSolve::deleteRecord(const QString& tableName, const QString& condition) {
    QString sql = QString("DELETE FROM %1 WHERE %2;").arg(tableName).arg(condition);
    return executeSql(sql);
}
// 示例：
// SQLiteSolve::instance().deleteRecord("student", "id=1");

bool SQLiteSolve::updateRecord(const QString& tableName, const QString& updateValues, const QString& condition) {
    QString sql = QString("UPDATE %1 SET %2 WHERE %3;").arg(tableName).arg(updateValues).arg(condition);
    return executeSql(sql);
}
// 示例：
// SQLiteSolve::instance().updateRecord("student", "age=21", "name='Tom'");

QVector<QVector<QString> > SQLiteSolve::selectRecord(const QString& tableName, const QString& field, const QString& condition) {
    QString sql;
    if (!field.isEmpty()) {
        if(condition.isEmpty()) {
            sql = QString("SELECT %1 FROM %2;").arg(field).arg(tableName);
        }else{

        sql = QString("SELECT %1 FROM %2 WHERE %3;").arg(field).arg(tableName).arg(condition);
        // qDebug()<<"111"<<endl;
        }

    } else {
        if(condition.isEmpty()) {
            sql = QString("SELECT * FROM %1;").arg(tableName);
        }
        else {
        sql = QString("SELECT * FROM %1 WHERE %2;").arg(tableName).arg(condition);
          //  qDebug()<<"121"<<endl;
        }
    }
   // qDebug()<<"NOW2:"<<sql<<endl;
    return querySql(sql);
}
// 示例：
// QVector<QVector<QString>> result;
// result = SQLiteSolve::instance().selectRecord("student", "", "name='Alice'");
// result = SQLiteSolve::instance().selectRecord("student", "name, age", "gender='male'");

QVector<QVector<QString> > SQLiteSolve::querySql(const QString& sql) {
    QVector<QVector<QString> > results;
    QSqlQuery query(m_database);
    if (!query.exec(sql)) {
        qDebug() << "Error: Failed to query sql." << query.lastError();
        return results;
    } else {
        while (query.next()) {
            QVector<QString> record;
            int count = query.record().count();
            for (int i = 0; i < count; ++i) {
                record.append(query.value(i).toString());
            }
            results.append(record);
        }
        qDebug() << "Successed to query sql." << sql;
        return results;
    }
}
