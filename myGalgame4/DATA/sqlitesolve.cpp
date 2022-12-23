#include "sqlitesolve.h"

SQLiteSolve::SQLiteSolve()
{

    db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("MyGalGame.db");

    db.open();

}
