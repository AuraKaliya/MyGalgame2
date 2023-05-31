#ifndef JSREADER_H
#define JSREADER_H


#include "updater.h"

#include "nowachievement.h"
#include "../Story/character.h"
#include "musicplayer.h"
#include "../UI/style.h"
#include "../UI/menuwidget.h"
#include "../UI/settingwidget.h"
#include "../UI/chievementwidget.h"
#include "../UI/rswidget.h"
#include "sourcetable.h"
#include "../UI/mainwidget.h"
#include "../Story/characterhub.h"

#include "../UI/characterwidget.h"
#include "../UI/characterinfoshowwidget.h"
#include "../UI/characterhubwidget.h"
#include "../UI/characterstoryshowwidget.h"
#include "../UI/tachielabel.h"
#include "../UI/carouselmapwidget.h"
#include "../UI/carouselwidget.h"
#include "../UI/storyinfowidget.h"
#include "../UI/choicewidget.h"
#include "../UI/storywidget.h"
#include "../UI/talkshowwidget.h"
#include "../UI/uiwidget.h"



#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSlider>
// 定义窗体大小结构体
struct WidgetRect {
    int left;
    int top;
    int width;
    int height;
};

// 定义部件设置结构体
struct WidgetSetting {
    QStringList labelNames; // Label名称列表
    QStringList buttonNames; // Button名称列表
    // TODO: 根据需求定义需要的属性
};

// 定义跳转信息结构体
struct LinkInfo {
    QString linkObjectName; // 需要进行连接的对象名称
    QString linkSignalName; // 需要连接的信号名称
    QString linkSlotName; // 需要连接的槽名称
};

// 定义资源信息结构体
struct ResourceInfo {
    QString pixUrl; // 地址
    QString status1; // 资源状态1
    QString status2; // 资源状态2
    QString status3; // 资源状态3
};
// 定义Label组信息结构体
struct LabelGroup {
    QString text; // 文本
    ResourceInfo pix; // 图片信息
    WidgetRect rect; // Label组矩形大小
    bool mask; // 是否遮盖
    int cardId; // 卡牌ID
    QString destination; // 目标
};
// 定义Label信息结构体
struct LabelInfo {
    QString labelName; // Label名称
    QString labelClass; // Label类别
    QList<LabelGroup> labelGroups; // Label组信息
    // TODO: 根据需求定义需要的属性
    QString labelLayout;
    int spaceH;
    int spaceV;
    WidgetRect rect;

};


// 定义Button组信息结构体
struct ButtonGroup {
    ResourceInfo pressPix; // 点击图片资源信息
    ResourceInfo normalPix; // 正常图片资源信息
    WidgetRect rect; // Button组矩形信息
    QString link; // 链接信息
};

// 定义Button信息结构体
struct ButtonInfo {
    QString buttonName; // Button名称
    QString buttonClass; // Button类别
    QList<ButtonGroup> buttonGroups; // Button组信息
    // TODO: 根据需求定义需要的属性
};


// 定义窗体位置结构体
struct WidgetPos {
    int x;
    int y;
};

// 定义部件信息结构体
struct WidgetInfo {
    QString widgetClass; // 部件类别
    WidgetRect rect; // 部件矩形大小
    WidgetSetting setting; // 部件设置
    WidgetPos pos; // 部件位置信息
    LinkInfo link; // 部件跳转信息
    // TODO：根据需求定义需要的属性
};

// 定义故事展示组件信息结构体
struct StoryShowWidgetInfo {
    WidgetInfo choiceWidgetInfo; // 选择部件信息
    WidgetInfo carousMapWidgetInfo; // CarouselMap部件信息
    WidgetInfo storyInfoWidgetInfo; // StoryInfo部件信息
    // TODO: 根据需求定义需要的属性
};





// 另一种方式
#define AUTOTYPE(type,value)  *((typeid(##value)*)type)


typedef void (*FUNC_Read)(UIWidget*,const QJsonObject&);

 class JSReader : public QObject
{
    Q_OBJECT

public:
    // ... 省略其他函数 ...
    JSReader();
    void readJsonFileToAchievement();  //读取JSON文件内容到NowAchievement中
    void readJsonFileToMusicPlayer();  //读取JSON文件内容到MusicPlayer中
    void readJsonFileToStyle();
    void readJsonFileToMenuWidget();
    void readJsonFileToSetting();
    void readJsonFileToReadAndSave();
    void readJsonFileToMainWidget();
    void readJsonFileToCharacterWidget();
    void readJsonFileToStory();
    QVector<Character*>readJsonFileToCharacter(); //读取JSON文件内容并返回

    void readJsonFile();

    static void setFilePath(const QString &filePath);  //设置读取路径

    void init();


public:
    static void read();
    static void readObject(UIWidget* parent,const QJsonObject &obj);
    static void readObject(QWidget* parent,const QJsonObject &obj);
    static void initObject(UIWidget* w,const QJsonObject &obj);
    int readInt(const QJsonObject &obj,const QString &key);
    QString readString(const QJsonObject &obj,const QString &key);
    static void  readRect(UIWidget* w,const QJsonObject &obj);
    static QObject* readBackgroundPix(const QJsonObject &obj);
    static void readSetting(UIWidget* w,const QJsonObject &obj);
    static void readStoryWidget( UIWidget*parent,const QJsonObject &obj);
    static void readTalkShowWidget( UIWidget*parent,const QJsonObject &obj);
    static void readTachieLabel( UIWidget*parent,const QJsonObject &obj);



private:
   // QMap<QString,FUNC_>

    //不用反射，我找到一个更好的方式，使用虚函数表获取函数指针，用map进行查询，用静态变量和单例进行类的注册
    static QMap<QString,FUNC_Read> m_ReadFunction;
    static QMap<QString,QString> m_Property2Type;
    static QMap<QString,UIWidget*> m_Name2Class;
    static QString m_filePath;

    NowAchievement * m_achievement;
    MusicPlayer * m_musicPlayer;
    MenuWidget * m_menuWidget;
    SettingWidget * m_settingWidget;
    RSWidget * m_rsWidget;
    SourceTable * m_sourceTable;
    MainWidget * m_mainWidget;
    CharacterHub * m_characterHub;
    CharacterWidget * m_characterWidget;
    CarouselWidget * m_carouselWidget;
    StoryWidget * m_storyWidget;

signals:
    void deckInfoUpdated(const QVector<QVector<QString> >& deckInfo);

};

#endif // JSREADER_H
