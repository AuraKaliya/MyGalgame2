#ifndef MODELLOVE_H
#define MODELLOVE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")
class ModelLove:public ModelBase

{
public:
    ModelLove(){};
    ModelLove(QString id, QString name, QString grade1_lines, QString grade2_lines, QString grade3_lines, QString grade4_lines);
    // 构造函数，用于创建一个ModelLove类的实例

    static void init(const QVector<QVector<QString> >& table);
    // 初始化函数，用于初始化静态表

    QString getLinesByGrade(const QString& Grade) const;
    // 根据等级获取台词

private:
    static QVector<QString> grade_list;
    static QVector<QVector<QString> > lines_table;
    // 静态变量，用于存储ModelLove类的数据表

    QString id_;
    QString name_;
    QString grade1_lines_;
    QString grade2_lines_;
    QString grade3_lines_;
    QString grade4_lines_;
    // 实例变量，存储一个ModelLove类的实例的数据
};
#endif // MODELLOVE_H
