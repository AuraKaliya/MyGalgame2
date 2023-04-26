#ifndef SQLITESOLVEFACTORY_H
#define SQLITESOLVEFACTORY_H

#include "sqlitesolve.h"

class SQLiteSolveFactory {
public:
    static SQLiteSolve create(const QString& db_name = "database.db") {
        SQLiteSolve solver(db_name);
        if (solver.open()) {
            return solver;
        } else {
            throw std::runtime_error("Failed to create SQLiteSolve object");
        }
    }
};
#endif // SQLITESOLVEFACTORY_H
