#include "storywidget.h"

StoryWidget * StoryWidget::m_instance=nullptr;

QMap<QString,FuncP> StoryWidget::m_textTypeGroup=QMap<QString,FuncP> ();

 Character * StoryWidget::m_nowCharacter=nullptr;
 Story * StoryWidget::m_nowStory=nullptr;
    //QStringList
 QVector<QString> StoryWidget::m_segmentGroup= QVector<QString>();
 TachieLabel* StoryWidget::m_talkerLabel=nullptr;
 TalkShowWidget * StoryWidget::m_talkShowWidget=nullptr;
 QPixmap* StoryWidget::m_backgroundPix=nullptr;
 int StoryWidget::m_nowSegIdx=0;



StoryWidget::StoryWidget(QWidget *parent)
    : UIWidget{parent}
{
    m_textTypeGroup.insert(QString("Options"),&StoryWidget::solveOption);
    m_textTypeGroup.insert(QString("TalkText"),&StoryWidget::solveTalkText);
    m_textTypeGroup.insert(QString("Background"),&StoryWidget::solveBackground);
    m_textTypeGroup.insert(QString("Character"),&StoryWidget::solveCharacter);
    m_textTypeGroup.insert(QString("Gesture"),&StoryWidget::solveGesture);
    m_textTypeGroup.insert(QString("PlusIntroduction"),&StoryWidget::solvePlusIntroduction);
}

StoryWidget *StoryWidget::getInstance(QWidget *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new StoryWidget(parent);
    }
    return m_instance;
}

void StoryWidget::setBackgroundPixUrl(QString url)
{
    m_backgroundPix=new QPixmap(url);
    //m_backgroundPix->load(url);
}

void StoryWidget::initTalkShowWidget(TalkShowWidget *talkShowWidget, QRect rect)
{
     if(m_talkShowWidget!=nullptr) delete m_talkShowWidget;
     m_talkShowWidget=talkShowWidget;
     m_talkShowWidget->setGeometry(rect);
     connect(m_talkShowWidget->getStoryShowLabel(),&storyShowLabel::segmentFinished,StoryWidget::getInstance(),&StoryWidget::nextSegment);
}

void StoryWidget::initTachieLabel(TachieLabel *tachieLabel, QRect rect)
{
     qDebug()<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh23";
    if(m_talkerLabel!=nullptr) delete m_talkerLabel;
    m_talkerLabel=tachieLabel;
    m_talkerLabel->setGeometry(rect);
}

void StoryWidget::setNowCharacter(QString name)
{
    QString  headUrl=CharacterHub::getInstance()->findCharacter(name)->headPixPath();
    m_talkShowWidget->setHead(QPixmap(headUrl));
}

void StoryWidget::setNowCharacterGesture(QString gesUrl)
{
    m_talkerLabel->setGesture(gesUrl);
}

void StoryWidget::setStory(Story * s)
{
    m_nowStory=s;
    m_segmentGroup.clear();
    QStringList tmpSeg = m_nowStory->text().split("|");
    m_segmentGroup=tmpSeg;
    m_nowSegIdx=0;
    qDebug()<<"Story:"<<m_nowStory;
    for(auto it:m_segmentGroup)
        qDebug()<<it;
}

void StoryWidget::startStory()
{
    qDebug()<<"Now SegmentCount"<<m_segmentGroup.size();
    m_nowSegIdx=0;
    StoryWidget::nextSegment();
}

void StoryWidget::nextSegment()
{
    //1. 处理文本  分割出 文本类型-背景-人物-表情-文本-后续指令
        //处理采用策略模式 分割符号为|$  (,-#@)(option)    (因为指令分割为#@)
        //此处不需要进行反射调用，只有在指令处理时才调用反射机制
        //eg:    Options:我们一起吧-Story#Character@Luwies#LoveUp@10,没什么兴趣-Story#Character@Luwies#LoveDown@10|
        //       Background:测试背景1$Character:Luwies$Gesture:正常$TalkText:这是一个测试$PlusIntroduction:Story#Character@Luwies#LoveUp@10,Story#Player@Player#GetMoney@100

    if(m_nowSegIdx<m_segmentGroup.size())
    {
        QString tmpText= m_segmentGroup[m_nowSegIdx];
        QStringList slipStr=tmpText.split("$");
        for(auto it : slipStr)
        {
            QString tmpKey=it.split(":")[0];
            QString tmpValue=it.split(":")[1];
            qDebug()<<tmpKey<<" "<<tmpValue;
            if(m_textTypeGroup.contains(tmpKey))
            m_textTypeGroup.value(tmpKey)(tmpValue);
        }
        ++m_nowSegIdx;
    }
    else
    {
        emit storyFinished();
    }
}

void StoryWidget::solveOption(QString s)
{
    //先用,分割不同选项 用-分割文本和指令 调用处理类对指令进行处理
    QStringList tmpStrL=s.split(",");
    QVector<QString> optionGroup;
    QVector<QString>OptionResultGroup;
    for(auto it:tmpStrL)
    {
        QString OptionText=it.split("-")[0];
        QString Instruction=it.split("-")[1];
        optionGroup<<OptionText;
        OptionResultGroup<<Instruction;
    }
    //进行Option显示

    //处理指令
    for(auto it :optionGroup)
        qDebug()<<it;
    for(auto it:OptionResultGroup)
        qDebug()<<it;

}

void StoryWidget::solveTalkText(QString s)
{
    qDebug()<<"setText "<<s;
    StoryWidget::getInstance()->m_talkShowWidget->setText(s);
}

void StoryWidget::solveBackground(QString s)
{
     qDebug()<<"m_backgroundPix "<<s;
    //StoryWidget::getInstance()->m_backgroundPix=QPixmap(s);
}

void StoryWidget::solveCharacter(QString s)
{

    StoryWidget::getInstance()->m_nowCharacter=CharacterHub::getInstance()->findCharacter(s);
     qDebug()<<CharacterHub::getInstance()->findCharacter(s)->getName()<<" "<<CharacterHub::getInstance()->findCharacter(s)->story();
     qDebug()<<StoryWidget::getInstance()->m_talkerLabel;

    StoryWidget::getInstance()->m_talkerLabel->initCharacter(StoryWidget::getInstance()->m_nowCharacter,StoryWidget::getInstance()->m_talkerLabel->geometry());

    StoryWidget::getInstance()->m_talkShowWidget->setHead(*new QPixmap(StoryWidget::getInstance()->m_nowCharacter->headPixPath()));

}

void StoryWidget::solveGesture(QString s)
{
   // qDebug()
    StoryWidget::getInstance()->m_talkerLabel->setGesture(StoryWidget::getInstance()->m_nowCharacter->getGesture(s));
}

void StoryWidget::solvePlusIntroduction(QString s)
{
     qDebug()<<s;
    QStringList tmpStrL=s.split(",");
    for(auto it:tmpStrL)
    {
      //处理指令
        qDebug()<<it;
    }
}

