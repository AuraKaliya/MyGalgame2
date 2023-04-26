#include "modelbattle.h"

// 初始化静态变量
// QVector<QVector<QString> > ModelBattle::battle_table;

// 默认构造函数
ModelBattle::ModelBattle() {}

// 带参构造函数
ModelBattle::ModelBattle(int atk, int def, int hp, int grade) {
    m_ATKGrowth = atk;
    m_DEFGrowth = def;
    m_HPGrowth = hp;
    m_Grade = grade;
}

// 设置ATKGrowth
void ModelBattle::setATKGrowth(int growth) {
    m_ATKGrowth = growth;
}

// 设置DEFGrowth
void ModelBattle::setDEFGrowth(int growth) {
    m_DEFGrowth = growth;
}

// 设置HPGrowth
void ModelBattle::setHPGrowth(int growth) {
    m_HPGrowth = growth;
}

// 设置Grade
void ModelBattle::setGrade(int grade) {
    m_Grade = grade;
}

// 获取ATKGrowth
int ModelBattle::getATKGrowth() const {
    return m_ATKGrowth;
}

// 获取DEFGrowth
int ModelBattle::getDEFGrowth() const {
    return m_DEFGrowth;
}

// 获取HPGrowth
int ModelBattle::getHPGrowth() const {
    return m_HPGrowth;
}

// 获取Grade
int ModelBattle::getGrade() const {
    return m_Grade;
}
