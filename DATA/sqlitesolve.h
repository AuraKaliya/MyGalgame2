#ifndef SQLITESOLVE_H
#define SQLITESOLVE_H

#include <QMutex>
#include <QSqlDatabase>
#include <QVariant>
#include <QVector>

#include <QDebug>

/**
 * @brief SQLite 数据库操作类
 */

class SQLiteSolve {
public:
    /**
     * 获取 SQLiteSolve 单例对象
     * @return SQLiteSolve 单例对象
     */
    static SQLiteSolve& instance();

    /**
     * 执行 SQL 语句
     * @param sql 要执行的 SQL 语句
     * @return 执行是否成功
     */
    bool executeSql(const QString& sql);

    /**
     * 添加记录
     * @param tableName 要插入数据的表名
     * @param values 要插入的记录的值，多个值以“|”为分隔符
     * @return 添加是否成功
     */
    bool addRecord(const QString& tableName, const QString& values);

    /**
     * 删除记录
     * @param tableName 要删除数据的表名
     * @param condition 删除记录的条件
     * @return 删除是否成功
     */
    bool deleteRecord(const QString& tableName, const QString& condition);

    /**
     * 更新记录
     * @param tableName 要更新数据的表名
     * @param updateValues 要更新的字段及其值，多个字段及值用逗号隔开，例如“name='Bob', age=20”
     * @param condition 更新记录的条件
     * @return 更新是否成功
     */
    bool updateRecord(const QString& tableName, const QString& updateValues, const QString& condition);

    /**
     * 查询记录
     * @param tableName 要查询数据的表名
     * @param field 要查询的字段，多个字段用逗号隔开，如果为空则表示查找所有字段
     * @param condition 查找记录的条件，如果为空则表示查找表中所有数据
     * @return 查询结果
     */
    QVector<QVector<QString> > selectRecord(const QString& tableName, const QString& field = "", const QString& condition="");

private:
    /**
     * 默认构造函数
     */
    SQLiteSolve();

    /**
     * 析构函数
     */
    ~SQLiteSolve();

    /**
     * 拷贝构造函数
     */
    SQLiteSolve(const SQLiteSolve&) = delete;

    /**
     * 赋值操作符重载
     */
    SQLiteSolve& operator=(const SQLiteSolve&) = delete;

    /**
     * 获取 QSqlDatabase 单例对象
     * @return QSqlDatabase 单例对象
     */
    QSqlDatabase& getDatabase();

    /**
     * 执行 SELECT 语句
     * @param sql 要执行的 SELECT 语句
     * @return 查询结果
     */
    QVector<QVector<QString> > querySql(const QString& sql);

private:
    static QMutex s_mutex; ///< 互斥锁
    static SQLiteSolve* s_sqliteSolve; ///< SQLiteSolve 单例对象
    QSqlDatabase m_database; ///< 数据库对象
};

#endif // SQLITESOLVE_H
