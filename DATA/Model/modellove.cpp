#include "modellove.h"

QVector<QString> ModelLove::grade_list = {};
QVector<QVector<QString>> ModelLove::lines_table = {};

ModelLove::ModelLove(QString id, QString name, QString grade1_lines, QString grade2_lines, QString grade3_lines, QString grade4_lines)
    : id_(id), name_(name), grade1_lines_(grade1_lines), grade2_lines_(grade2_lines), grade3_lines_(grade3_lines), grade4_lines_(grade4_lines) {}
    // 构造函数的实现，用于创建一个ModelLove类的实例

void ModelLove::init(const QVector<QVector<QString>>& table) {
    grade_list.clear();
    lines_table.clear();
    // 清空静态变量的内容

    for (auto row : table) {
        grade_list.append(row[0]);
        // 将台词等级名称添加到列表中
        QVector<QString> lines;
        for (int i = 1; i < row.size(); ++i) {
            lines.append(row[i]);
            // 将台词添加到向量中
        }
        lines_table.append(lines);
        // 将向量添加到二维列表中，组成ModelLove类的静态数据表
    }
}

QString ModelLove::getLinesByGrade(const QString& Grade) const {
    int idx = grade_list.indexOf(Grade);
    // 获取等级在grade_list中的索引
    if (idx < 0 || idx >= lines_table.size()) {
        return "";
        // 如果等级不存在或索引不合法，则返回空字符串
    }
    return lines_table[idx][0];
    // 返回对应等级的第一句台词
}
// 获取等级对应的台词的函数的实现
