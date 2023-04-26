#include "modelbuff.h"

QVector<int> ModelBUFF::id_list = {};
QVector<QString> ModelBUFF::name_list = {};
QVector<QString> ModelBUFF::desc_list = {};
QVector<QString> ModelBUFF::instr_list = {};
QVector<QString> ModelBUFF::icon_list = {};

void ModelBUFF::init(const QVector<QVector<QString> >& table) {
    id_list.clear();
    name_list.clear();
    desc_list.clear();
    instr_list.clear();
    icon_list.clear();
    // 清空静态变量的内容

    for (const auto& row : table) {
        id_list.append(row[0].toInt());
        name_list.append(row[1]);
        desc_list.append(row[2]);
        instr_list.append(row[3]);
        icon_list.append(row[4]);
        // 将每一行数据中的 id, name, desc, instr 和 icon 依次添加到对应的向量中
    }
}

QString ModelBUFF::getNameByID(int id) const {
    int index = id_list.indexOf(id);
    if (index == -1) {
        return "";
    } else {
        return name_list[index];
    }
}

QString ModelBUFF::getDescriptionByID(int id) const {
    int index = id_list.indexOf(id);
    if (index == -1) {
        return "";
    } else {
        return desc_list[index];
    }
}

QString ModelBUFF::getInstructionByID(int id) const {
    int index = id_list.indexOf(id);
    if (index == -1) {
        return "";
    } else {
        return instr_list[index];
    }
}

QString ModelBUFF::getIconByID(int id) const {
    int index = id_list.indexOf(id);
    if (index == -1) {
        return "";
    } else {
        return icon_list[index];
    }
}
