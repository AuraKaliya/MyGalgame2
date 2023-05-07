#ifndef INSTRUCTIONSOLVER_H
#define INSTRUCTIONSOLVER_H

#include <QObject>
#include "instruction.h"
#include <QString>
#include <QVector>
#include <QMap>
#include <QMutex>

class InstructionSolver : public QObject
{
    Q_OBJECT
public:
    static InstructionSolver* getInstance(QObject* parent = nullptr); //获取单例对象
    void init(Instruction &instruction);
    void solution();  //处理指令


typedef std::function<void(QString name, QString value)> FuncPtr;

signals:
    void playerGetMoney(QString name,QString value);  //玩家获取金币
    void playerLoseMoney(QString name,QString value); //玩家失去金币
    void playerGetAchievement(QString name,QString serialNumber); //达成成就

    void storyEnding(QString name,QString serialNumber);  //剧情完成
    void storyUnlock(QString name,QString serialNumber);  //剧情解锁
    void storyJump(QString name,QString serialNumber);//剧情跳转

    void characterLoveUp(QString name,QString value);   //角色好感度上升
    void characterLoveDown(QString name,QString value); //角色好感度下降
    void characterUnlock(QString name,QString serialNumber); //角色解锁



private:
    static InstructionSolver* instance;
    static QMutex mutex;
    QMap<QString, FuncPtr> funcTable;
    Instruction m_instruction;

    explicit InstructionSolver(QObject *parent = nullptr);
    InstructionSolver(const InstructionSolver&);

    ~InstructionSolver();

    void emitPlayerGetMoney(QString name, QString value);
    void emitPlayerLoseMoney(QString name, QString value);
    void emitPlayerGetAchievement(QString name, QString serialNumber);
    void emitStoryEnding(QString name, QString serialNumber);
    void emitStoryUnlock(QString name, QString serialNumber);
    void emitCharacterLoveUp(QString name, QString value);
    void emitCharacterLoveDown(QString name, QString value);
    void emitCharacterUnlock(QString name, QString serialNumber);
    void emitStoryJump(QString name, QString serialNumber);
};

#endif // INSTRUCTIONSOLVER_H
