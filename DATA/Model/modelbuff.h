#ifndef MODELBUFF_H
#define MODELBUFF_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")

class ModelBUFF : public ModelBase {
public:
    static void init(const QVector<QVector<QString > >& table);

    static QVector<int> id_list;
    static QVector<QString> name_list;
    static QVector<QString> desc_list;
    static QVector<QString> instr_list;
    static QVector<QString> icon_list;

    QString getNameByID(int id) const;
    QString getDescriptionByID(int id) const;
    QString getInstructionByID(int id) const;
    QString getIconByID(int id) const;
};

#endif // MODELBUFF_H
