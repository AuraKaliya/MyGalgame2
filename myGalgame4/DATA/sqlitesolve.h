#ifndef SQLITESOLVE_H
#define SQLITESOLVE_H


#include <QSqlDatabase>
#include <QSqlQuery>    //DML DDL
#include <QSqlQueryModel>
#include <QSqlError>


class SQLiteSolve
{

public:
    SQLiteSolve();

   /**通过函数来进行语句区分和编辑**/



private:
    QSqlDatabase db;


};

#endif // SQLITESOLVE_H
