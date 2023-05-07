#ifndef DATAREADER_H
#define DATAREADER_H


class DataReader
{
public:
    DataReader();
};

#endif // DATAREADER_H
/*
//该类用于读取配置文件并进行游戏初始化。
工作流程为：当sqlite中存有游戏信息时，进行数据库交互查询并初始化游戏，当没有或需要手动导入配置时，读取excel对数据库进行配置，并通过数据库进行初始化设置。


*/
