#include "sqlitesolve.h"

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

SQLiteSolve& SQLiteSolve::instance() {
    static SQLiteSolve sol("database.db");
    return sol;
}

bool SQLiteSolve::open() {
    if (m_database.isOpen()) {
        return true;
    }
    return m_database.open();
}

void SQLiteSolve::close() {
    m_database.close();
}

bool SQLiteSolve::executeSql(const QString& sql) {
    QSqlQuery query(m_database);
    bool ok = query.exec(sql);
    if (!ok) {
        qDebug() << "Error executing SQL statement: " << sql;
        qDebug() << "Error message: " << query.lastError().text();
    }
    return ok;
}

QVector<QVector<QString>> SQLiteSolve::querySql(const QString& sql) {
    QVector<QVector<QString>> result;
    QSqlQuery query(m_database);
    bool ok = query.exec(sql);
    if (!ok) {
        qDebug() << "Error executing SQL statement: " << sql;
        qDebug() << "Error message: " << query.lastError().text();
        return result;
    }
    QSqlRecord record = query.record();
    while (query.next()) {
        QVector<QString> row;
        for (int i = 0; i < record.count(); i++) {
            row.append(query.value(i).toString());
        }
        result.append(row);
    }
    return result;
}

SQLiteSolve::SQLiteSolve(const QString& db_name) {
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(db_name);
}

SQLiteSolve::~SQLiteSolve() {
    close();
}
