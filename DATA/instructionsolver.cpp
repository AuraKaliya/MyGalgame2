#include "instructionsolver.h"

InstructionSolver* InstructionSolver::instance = nullptr;
QMutex InstructionSolver::mutex;

InstructionSolver::InstructionSolver(QObject *parent) : QObject(parent)
{
    // 构造函数

    // 初始化指令与函数的映射
    funcTable["getMoney"] = std::bind(&InstructionSolver::emitPlayerGetMoney, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["loseMoney"] = std::bind(&InstructionSolver::emitPlayerLoseMoney, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["getAchievement"] = std::bind(&InstructionSolver::emitPlayerGetAchievement, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["storyEnding"] = std::bind(&InstructionSolver::emitStoryEnding, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["storyUnlock"] = std::bind(&InstructionSolver::emitStoryUnlock, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["characterLoveUp"] = std::bind(&InstructionSolver::emitCharacterLoveUp, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["characterLoveDown"] = std::bind(&InstructionSolver::emitCharacterLoveDown, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["characterUnlock"] = std::bind(&InstructionSolver::emitCharacterUnlock, this, std::placeholders::_1, std::placeholders::_2);
    funcTable["storyJump"] = std::bind(&InstructionSolver::emitStoryJump, this, std::placeholders::_1, std::placeholders::_2);
}

InstructionSolver* InstructionSolver::getInstance(QObject* parent)
{
    if (instance == nullptr)
    {
        QMutexLocker locker(&mutex);
        if (instance == nullptr)
        {
            instance = new InstructionSolver(parent);
        }
    }
    return instance;
}

InstructionSolver::~InstructionSolver()
{
    // 析构函数
}

void InstructionSolver::init(Instruction &instruction)
{
    m_instruction = instruction;
}



void InstructionSolver::emitPlayerGetMoney(QString name, QString value)
{
    emit playerGetMoney(name, value);
}

void InstructionSolver::emitPlayerLoseMoney(QString name, QString value)
{
    emit playerLoseMoney(name, value);
}

void InstructionSolver::emitPlayerGetAchievement(QString name, QString serialNumber)
{
    emit playerGetAchievement(name, serialNumber);
}

void InstructionSolver::emitStoryEnding(QString name, QString serialNumber)
{
    emit storyEnding(name, serialNumber);
}

void InstructionSolver::emitStoryUnlock(QString name, QString serialNumber)
{
    emit storyUnlock(name, serialNumber);
}

void InstructionSolver::emitCharacterLoveUp(QString name, QString value)
{
    emit characterLoveUp(name, value);
}

void InstructionSolver::emitCharacterLoveDown(QString name, QString value)
{
    emit characterLoveDown(name, value);
}

void InstructionSolver::emitCharacterUnlock(QString name, QString serialNumber)
{
    emit characterUnlock(name, serialNumber);
}

void InstructionSolver::emitStoryJump(QString name, QString serialNumber)
{
    emit storyJump(name, serialNumber);
}

void InstructionSolver::solution()
{
    // 提取指令
    QString targetAction = m_instruction.insObject();
    QString operation = m_instruction.insDoing();

    // 根据指令映射到对应的函数并调用
    QString tmpStr, name, value;
    if (targetAction.contains("player")) {
        tmpStr = "player";
        name = targetAction.split(":")[1];
    } else if (targetAction.contains("story")) {
        tmpStr = "story";
        name = targetAction.split(":")[1];
    } else if (targetAction.contains("character")) {
        tmpStr = "character";
        name = targetAction.split(":")[1];
    }

    QStringList opList = operation.split(":");
    QString funcName = tmpStr + opList[0]; // 修正funcName的构造方式
    value = opList[1];

    if (funcTable.contains(funcName))
    {
        funcTable[funcName](name, value);
    }
}
