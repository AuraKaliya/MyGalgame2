#ifndef SQLITESOLVE_H
#define SQLITESOLVE_H

#include <QSqlDatabase>

class SQLiteSolve {
public:
    static SQLiteSolve& instance();

    bool open();
    void close();

    bool executeSql(const QString& sql);
    QVector<QVector<QString>> querySql(const QString& sql);

private:
    explicit SQLiteSolve(const QString& db_name);
    ~SQLiteSolve();

    SQLiteSolve(const SQLiteSolve&) = delete;
    SQLiteSolve& operator=(const SQLiteSolve&) = delete;
    SQLiteSolve(SQLiteSolve&&) = delete;
    SQLiteSolve& operator=(SQLiteSolve&&) = delete;

    QSqlDatabase m_database;
};

#endif // SQLITESOLVE_H
