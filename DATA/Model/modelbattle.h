#ifndef MODELBATTLE_H
#define MODELBATTLE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")
class ModelBattle : public ModelBase {
public:
    ModelBattle();  // 默认构造函数
    ModelBattle(int atk, int def, int hp, int grade);  // 带参构造函数

    void setATKGrowth(int growth);  // 设置ATKGrowth
    void setDEFGrowth(int growth);  // 设置DEFGrowth
    void setHPGrowth(int growth);   // 设置HPGrowth
    void setGrade(int grade);       // 设置Grade

    int getATKGrowth() const;  // 获取ATKGrowth
    int getDEFGrowth() const;  // 获取DEFGrowth
    int getHPGrowth() const;   // 获取HPGrowth
    int getGrade() const;      // 获取Grade

    // 省略其他可能需要的成员函数

private:
    int m_ATKGrowth;  // ATKGrowth成员变量
    int m_DEFGrowth;  // DEFGrowth成员变量
    int m_HPGrowth;   // HPGrowth成员变量
    int m_Grade;      // Grade成员变量

    // static QVector<QVector<QString> > battle_table;  // 静态二维表
};



#endif // MODELBATTLE_H
