#《Luck No Complete》 技术点整理

* 项目回顾

    本项目初步尝试Data-Tool-UI三层结构框架，初步尝试使用json文件对程序进行外部数据配置，整理音源播放、存档存读、自定义组件的页面切换和数据传递等功能，同时探索了轮播图、可平滑伸缩角色栏、看板娘动作切换、指令驱动等技术。

* 技术点

    * Json文件读取的几种方式

        通用读取流程：在使用Qt进行Json文件读取时，通常需要引入以下文件：

        ```c++
        #include <QJsonDocument>
        #include <QJsonObject>
        #include <QJsonArray>
        #include <QJsonValue>
        ```

        在读取类中应存在一个read()函数、一个setPath(QString)函数。

        标准开头如下，根据实际需求进行增删：

        ```c++
        QFile file(m_filePath);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // 打开文件失败
                return;
            }
        
            QString jsonStr = file.readAll();
            file.close();
        
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
            if (parseError.error != QJsonParseError::NoError) {
                // 解析json内容失败
                return;
            }
        ```

        在探索如何进行数据读取的道路上，本人尝试过以下方法：

        ①自定义结构体进行临时数据存储和传递，在相应类中进行处理。

        ​	这种方案其实算“失败”的案例，因为“相应类”通常为Qt的组件，所需要转化的数据为QString、QRect、QSize等，不如一开始就以这些数据结构进行临时数据的读取。

        ②仅载入配置的数据信息，在程序内的UI层进行页面的构建，通过Init()函数确保单例页面的实例化，通过QMap<QString,QWidget*>进行指定配置。

        ​	这种方案还算成功，效果显著，但美中不足的是项目的拓展性不够，仅配置数据能在外部进行更改，初始化方案在程序内写死。此外，读取类需要引入大量的页面类文件，同时也需要把QMap写成Static形式，而基于QMap进行寻找相应页面类的读取函数也必须要以Static形式出现，这种情况对一个工程项目而言并不好。

        ​	此方案用到一个技术点是通过typeof关键字定义函数指针，在读取类的构建时进行字典构建和相应类的初始化。

        ```c++
        typedef void (*FUNC_Read)(UIWidget*,const QJsonObject&);
        static QMap<QString,FUNC_Read> m_ReadFunction;
        
        //这个想法应当被记录，虽然用在此处并不合适，但不失为一种替代性的反射机制的实现办法
        
        ```

        ③尝试将单独的页面配置文件合并为整体的配置文件，通过结构化手段进行读取。

        ​	这种方案是一个成功的尝试，并在下一个项目《Mirro And Flowers》中得到良好的应用。整体思路是提取两个配置文件中的共同点，将配置方法进行归类划分，并以过程的方式进行配置。初步实践中采用Name、Rect、Setting、Contains的方式实现读取流程，在Setting中进行读取函数的更详细划分；后续改进为从QWidget中引出一个UIWidget作为项目UI页面的基类，通过调用该BaseClass的虚函数实现Setting中的配置，这样不仅提高了程序的拓展性，也使项目构建过程中更有逻辑，使读取类的结构变得简单易懂。

    * 通过Updater类实现的组件行为/状态监测

        其实，这个技术点应该属于观察者模式的应用，其思路是使用一个观察者类Updater，通过addObject函数添加监控对象，并提供监测通道（如信号传递），在Updater类的内部实现功能分化的槽函数UpdateLabel/UpdateWidget/UpdateImage等，达到通过中间类来调整整个项目的组件状态转化的功能。

        在本项目中，本人应用该方法进行自定义Label的点击状态的切换，在JumpLabel中仅配置需要切换的图片地址和跳转目标指针，鼠标点击事件发生时，由Updater进行捕获并执行图片切换（即Label被按下状态）和跳转至目标页面。

    * 通过指令系统实现的事件触发功能

        这是对反射机制的一个实践，通过预编译实现反射方法并在进入剧情时顺序处理剧情文本、剧情相关角色、剧情后续影响，这是一个成功的尝试，能够让开发者在程序外通过对文本的调整达到影响角色相关属性（如好感度）的功能。

        相关代码：

        ```c++
        //指令类和工厂类的实现基于反射机制，不再赘述。
        //指令处理类
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
        
        #include "instructionsolver.h"
        
        InstructionSolver* InstructionSolver::instance = nullptr;
        QMutex InstructionSolver::mutex;
        
        InstructionSolver::InstructionSolver(QObject *parent) : QObject(parent)
        {
            // 构造函数
        
            // 初始化指令与函数的映射
            funcTable["PlayerGetMoney"] = std::bind(&InstructionSolver::emitPlayerGetMoney, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["PlayerLoseMoney"] = std::bind(&InstructionSolver::emitPlayerLoseMoney, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["PlayerGetAchievement"] = std::bind(&InstructionSolver::emitPlayerGetAchievement, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["StoryEnding"] = std::bind(&InstructionSolver::emitStoryEnding, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["StoryUnlock"] = std::bind(&InstructionSolver::emitStoryUnlock, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["CharacterLoveUp"] = std::bind(&InstructionSolver::emitCharacterLoveUp, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["CharacterLoveDown"] = std::bind(&InstructionSolver::emitCharacterLoveDown, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["CharacterUnlock"] = std::bind(&InstructionSolver::emitCharacterUnlock, this, std::placeholders::_1, std::placeholders::_2);
            funcTable["StoryJump"] = std::bind(&InstructionSolver::emitStoryJump, this, std::placeholders::_1, std::placeholders::_2);
        
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
            //Story#Player@Player#GetMoney@100
            // 提取指令
            QString targetAction = m_instruction.insObject();
            QString operation = m_instruction.insDoing();
        
            // 根据指令映射到对应的函数并调用
            QString tmpStr, name, value;
            if (targetAction.contains("Player")) {
                tmpStr = "Player";
                name = targetAction.split("@")[1];
            } else if (targetAction.contains("Story")) {
                tmpStr = "Story";
                name = targetAction.split("@")[1];
            } else if (targetAction.contains("Character")) {
                tmpStr = "Character";
                name = targetAction.split("@")[1];
            }
        
            QStringList opList = operation.split("@");
            QString funcName = tmpStr + opList[0]; // 修正funcName的构造方式
            value = opList[1];
        
            if (funcTable.contains(funcName))
            {
                funcTable[funcName](name, value);
            }
        }
        
        
        //相关应用UI：剧情页面
        #ifndef STORYWIDGET_H
        #define STORYWIDGET_H
        
        #include <QWidget>
        #include <QMap>
        
        #include "uiwidget.h"
        #include "tachielabel.h"
        #include "talkshowwidget.h"
        #include "../DATA/Story/character.h"
        #include "../DATA/Story/characterhub.h"
        #include "../DATA/Story/story.h"
        
        #include "../DATA/instructionfactory.h"
        
        typedef void (*FuncP)(QString) ;
        
        class StoryWidget : public UIWidget
        {
            Q_OBJECT
        public:
            static StoryWidget* getInstance(QWidget * parent=nullptr);
        
           void setBackgroundPixUrl(QString) override;
           void initTalkShowWidget(TalkShowWidget * talkShowWidget,QRect rect) override;
           void initTachieLabel(TachieLabel* tachieLabel,QRect rect) override;
           static void setNowCharacter(QString name);
           static void setNowCharacterGesture(QString gesUrl);
           static void setStory(Story*);
           static void startStory();
        
        
        public slots:
             void nextSegment();
        
        private slots:
           static void solveOption(QString);
           static void solveTalkText(QString);
           static void solveBackground(QString);
           static void solveCharacter(QString);
           static void solveGesture(QString);
           static void solvePlusIntroduction(QString);
            // void showOption();
        signals:
            void storyFinished();
        private:
            static StoryWidget* m_instance;
            explicit StoryWidget(QWidget *parent = nullptr);
            static  QMap<QString,FuncP> m_textTypeGroup;
        
           static Character * m_nowCharacter;
           static Story * m_nowStory;
            //QStringList
           static QVector<QString> m_segmentGroup;
           static TachieLabel* m_talkerLabel;
           static TalkShowWidget * m_talkShowWidget;
           static  QPixmap* m_backgroundPix;
           static  int m_nowSegIdx;
        
        };
        
        #endif // STORYWIDGET_H
        
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
            StoryWidget::getInstance()->nextSegment();
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
                QString insType=it.split("#")[2].split("@")[0];
                Instruction* ins=InstructionFactory::getInstance()->creatInstruction(QString("Instruction_"+insType));
                if(ins!=nullptr)
                {
                    qDebug()<<"Solute!";
                    ins->soluteInstruction(it);
                }
                else
                qDebug()<<"No Have This Ins";
            }
        }
        
        ```

    * 模拟原神的双状态角色界面UI

        这部分想法出来时先做了一个原型进行尝试，在获得成功后在本项目中应用。

        整体来说，是为一个页面设置两种状态（展开和收缩），规划两种状态的页面大小和位置，通过一个可移动滑块在规定区域内滑动，根据滑块的位置信息或相关反馈选择展开或收缩状态，技术难度并不大。

        相关代码：

        ```c++
        //页面代码
        #ifndef CHARACTERHUBWIDGET_H
        #define CHARACTERHUBWIDGET_H
        
        #include <QWidget>
        #include <QStackedLayout>
        #include <QGridLayout>
        #include <QVBoxLayout>
        #include <QScrollArea>
        
        #include <QMap>
        #include <QVector>
        
        #include "jumplabel.h"
        #include "searchblok.h"
        #include "slideblock.h"
        #include "../DATA/Story/characterhub.h"
        #include "characterinfoshowwidget.h"
        
        class CharacterHubWidget : public QWidget
        {
            Q_OBJECT
        public:
            explicit CharacterHubWidget(QWidget *parent = nullptr);
            void initCharacterHub();
        
            void initRect(QRect showRect,QRect hideRect);
            void initCardSize(QSize cardSize,QSize cardSmallSize);
            void initAreaRect(QRect showRect,QRect hideRect);
        
            void setSpace(int sp);
            void setbackground();
        
        
        public slots:
            void hideWidget();
            void showWidget();
            void characterChoiced(int);
        
        
        signals:
            void characterClicked(Character*);
            void widgetHide();
            void widgetShow();
        private:
            Searchblok * m_searchBlock;
            SlideBlock * m_slideBlock;
        
            QScrollArea * m_characterShowArea;
            QWidget * m_characterShowWidget;
            QVector <JumpLabel*> m_characterLabelGroup;
        
            QRect m_showRect;
            QRect m_hideRect;
            QSize m_cardSize;
            QSize m_cardSmallSize;
            int m_space;
        
        
        
            QRect m_showAreaRect;
            QRect m_showWidgetRect;
            QRect m_hideWidgetRect;
            QRect m_hideAreaRect;
        
        
            QStackedLayout *m_stackedLayout;
            QGridLayout *m_showLayout;
            QGridLayout *m_hideLayout;
        
        
        };
        
        #endif // CHARACTERHUBWIDGET_H
         #include "characterhubwidget.h"
        
        
        CharacterHubWidget::CharacterHubWidget(QWidget *parent)
            : QWidget{parent}
        {
            resize(450,900);
           setWindowFlags(Qt::FramelessWindowHint);
           //setAttribute(Qt::WA_TranslucentBackground,true);
        
            m_searchBlock=new Searchblok();
            m_searchBlock->setParent(this);
            m_searchBlock->setGeometry(25,50,400,30);
        
            m_characterShowArea=new QScrollArea(this);
            m_characterShowWidget=new QWidget(m_characterShowArea);
        
            m_characterShowArea->setGeometry(25,100,400,600);
        
            m_characterShowArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            m_characterShowArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        
            m_characterShowWidget->setWindowFlags(Qt::FramelessWindowHint);
            m_characterShowArea->setWidget(m_characterShowWidget);
            m_showAreaRect=m_characterShowArea->geometry();
            m_characterShowWidget->setGeometry(m_showAreaRect);
        
        
           // m_stackedLayout=new QStackedLayout();
            m_showLayout=new QGridLayout();
        
        
        
        
        
        
           // m_stackedLayout->
        //    for(int i=1;i<5;i++)
        //    {
        //        JumpLabel * tmpJ=new JumpLabel(m_characterShowWidget);
        //        m_characterLabelGroup<<tmpJ;
        //        tmpJ->setPixmapPathGroup(":/UI/RESOURCE/test_CharacterCardPix"+QString::number(i)+".png",":/UI/RESOURCE/test_CharacterCardSmallPix"+QString::number(i)+".png");
        //        tmpJ->setFixedSize(90,120);
        //        m_showLayout->addWidget(tmpJ,(i-1)/3,(i-1)%3,Qt::AlignCenter);
        //        m_characterShowWidget->resize(m_characterShowWidget->width(),((i-1)/3+1)*150);
        //    }
        
           // m_characterShowWidget->setLayout(m_showLayout);
        
            m_showLayout->setSpacing(10);
            m_showLayout->setContentsMargins(0,5,0,5);
        
        
            m_showWidgetRect=m_characterShowWidget->geometry();
        
            //m_hideAreaRect=QRect(25,100,85,600);
            //m_hideWidgetRect=QRect(0,0,85,m_characterLabelGroup.size()*70);
        
        
        
        
        
        
        
        
            m_slideBlock=new SlideBlock();
            m_slideBlock->setParent(this);
            m_slideBlock->setRect(QRect(25,775,400,85));
            m_slideBlock->setGeometry(340,775,85,85);
            m_slideBlock->setFixPos(m_slideBlock->pos());
        
        
            connect(m_slideBlock,&SlideBlock::valueMax,this,&CharacterHubWidget::hideWidget);
            connect(m_slideBlock,&SlideBlock::reset,this,&CharacterHubWidget::showWidget);
        
        
            setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency3.png);");
            //hideWidget();
        
        }
        
        void CharacterHubWidget::initCharacterHub()
        {
            int i=0;
            for(auto it:CharacterHub::getInstance()->getCharaList())
            {
                JumpLabel * tmpJ=new JumpLabel(m_characterShowWidget);
                m_characterLabelGroup<<tmpJ;
                tmpJ->setCardID(it->getID());
               //tmpJ->setPixmapPathGroup(":/UI/RESOURCE/test_CharacterCardPix"+QString::number(i)+".png",":/UI/RESOURCE/test_CharacterCardSmallPix"+QString::number(i)+".png");
                tmpJ->setPixmapPathGroup(it->cardPixPath(),it->cardSmallPixPath());
                tmpJ->setFixedSize(m_cardSize);
        //        tmpJ->setFixedSize(m_cardSize);
        //        m_showLayout->addWidget(tmpJ,(i)/3,(i)%3,Qt::AlignCenter);
                m_characterShowWidget->resize(m_characterShowWidget->width(),((i-1)/3+1)*150);
                m_showLayout->addWidget(tmpJ,(i)/3,(i)%3,Qt::AlignCenter);
                m_characterShowWidget->setLayout(m_showLayout);
                connect(tmpJ,&JumpLabel::choiceCard,this,&CharacterHubWidget::characterChoiced);
        
                ++i;
            }
        
             m_hideWidgetRect=QRect(0,0,85,m_characterLabelGroup.size()*70);
            CharacterInfoShowWidget::getInstance()->initCharacterInfomation(CharacterHub::getInstance()->findCharacter(m_characterLabelGroup[0]->getCardID()));
             emit characterClicked(CharacterHub::getInstance()->findCharacter(m_characterLabelGroup[0]->getCardID()));
        }
        
        void CharacterHubWidget::initRect(QRect showRect, QRect hideRect)
        {
            m_showRect=showRect;
            m_hideRect=hideRect;
        }
        
        void CharacterHubWidget::initCardSize(QSize cardSize, QSize cardSmallSize)
        {
            m_cardSize=cardSize;
            m_cardSmallSize=cardSmallSize;
        }
        
        void CharacterHubWidget::initAreaRect(QRect showRect, QRect hideRect)
        {
            m_showAreaRect=showRect;
            m_hideAreaRect=hideRect;
        }
        
        void CharacterHubWidget::setSpace(int sp)
        {
            m_space=sp;
        }
        
        
        
        void CharacterHubWidget::hideWidget()
        {
            delete m_showLayout;
            m_showLayout=new QGridLayout();
            int i=0;
            for (auto it:m_characterLabelGroup)
            {
                it->changePix();
                //it->setFixedSize(65,65);
                it->setFixedSize(m_cardSmallSize);
                m_showLayout->addWidget(it,i++,0,Qt::AlignCenter);
            }
        
            //m_characterShowArea->setGeometry(25,100,85,600);
            m_characterShowArea->setGeometry(m_hideAreaRect);
            m_characterShowWidget->setGeometry(0,0,m_hideAreaRect.width(),m_characterLabelGroup.size()*70);
        
            m_characterShowWidget->setLayout(m_showLayout);
            m_searchBlock->setVisible(false);
            resize(m_hideRect.size());
        
            emit widgetHide();
        
        }
        
        void CharacterHubWidget::showWidget()
        {
        
            delete m_showLayout;
            m_showLayout=new QGridLayout();
            int i=0;
            for (auto it:m_characterLabelGroup)
            {
                it->changePix();
                //it->setFixedSize(90,120);
                it->setFixedSize(m_cardSize);
                m_showLayout->addWidget(it,i/3,i%3,Qt::AlignCenter);
                ++i;
            }
        
            m_characterShowArea->setGeometry(m_showAreaRect);
            m_characterShowWidget->setGeometry(0,0,m_characterShowArea->width(),((i-1)/3+1)*150);
            m_characterShowWidget->setLayout(m_showLayout);
        
            m_searchBlock->setVisible(true);
            resize(m_showRect.size());
        
            emit widgetShow();
        }
        
        void CharacterHubWidget::characterChoiced(int id)
        {
            Character* tmp=CharacterHub::getInstance()->findCharacter(id);
            CharacterInfoShowWidget::getInstance()->initCharacterInfomation(tmp);
            emit characterClicked(tmp); //  不行 需要新建一个用于paint立绘的类
        }
        
        
        //滑块代码
        #ifndef SLIDEBLOCK_H
        #define SLIDEBLOCK_H
        
        #include <QPushButton>
        #include <QObject>
        #include <QRect>
        #include <QMouseEvent>
        
        
        class SlideBlock : public QPushButton
        {
            Q_OBJECT
        public:
            SlideBlock();
            void setRect(QRect rect);
            void mousePressEvent(QMouseEvent * e)override;
            void mouseMoveEvent(QMouseEvent *e)override;
            void mouseReleaseEvent(QMouseEvent * e) override;
            void initPos();
            void resetPos();
            void setMouseStartPos(QPoint newMouseStartPos);
        
            void setFixPos(QPoint newFixPos);
        
        signals:
            void valueMax();
            void reset();
        private:
            QRect m_abRect;
            QPoint m_mouseStartPos;
            QPoint fixPos;
            QPoint m_btnStarPos;
            int values;
            bool m_isPressed;
        
        };
        
        #endif // SLIDEBLOCK_H
        #include "slideblock.h"
        
        SlideBlock::SlideBlock()
        {
            m_isPressed=false;
            values=0;
        
        
        }
        
        void SlideBlock::setRect(QRect rect)
        {
            m_abRect=rect;
        }
        
        void SlideBlock::mousePressEvent(QMouseEvent *e)
        {
            m_isPressed=true;
            m_mouseStartPos=e->pos();
            qDebug()<<m_mouseStartPos;
            m_btnStarPos=this->frameGeometry().topLeft();
        
        }
        
        void SlideBlock::mouseMoveEvent(QMouseEvent *e)
        {
            if((m_isPressed&&(this->x()>=m_abRect.x()))&&(values==0))
            {
               QPoint distance=e->pos()-m_mouseStartPos;
                //this->move((m_btnStarPos+distance).x(),m_btnStarPos.y());
               this->move(distance.x()+this->x(),m_btnStarPos.y());
                //this->move(e->pos().x()+this->x()-e->pos().x(),m_btnStarPos.y());
            }
        }
        
        void SlideBlock::mouseReleaseEvent(QMouseEvent *e)
        {
            m_isPressed=false;
            if((this->x()<m_abRect.x()+10)&&(values==0))
            {
                this->move(m_abRect.x(),m_abRect.y());
               values=1;
                emit valueMax();
            }
            else
            {
        
                resetPos();
                if(values==1)
                {
                    emit reset();
                    values=0;
                }
        
            }
        }
        
        void SlideBlock::initPos()
        {
        
        }
        
        void SlideBlock::resetPos()
        {
            move(fixPos);
        }
        
        void SlideBlock::setMouseStartPos(QPoint newMouseStartPos)
        {
           // m_mouseStartPos = newMouseStartPos;
            //m_mouseStartPos=QPoint(0,0);
            qDebug()<<m_mouseStartPos;
        }
        
        void SlideBlock::setFixPos(QPoint newFixPos)
        {
            fixPos = newFixPos;
        }
        ```

    * 轮播图实现

        参考网上的一些方案后，本人根据自己的理解进行了一些实践，相关实践结果已有相应的原型。

        实现思路为：确定当前图的Size和其余图的Size，通过容器对组件进行管理，设置整体前移和后移的方法并传递当前图片的下标，根据实际容器大小进行移动或不动，动画方面用到了<QPropertyAnimation>和<QParallelAnimationGroup>。

        该技术点有以下需要注意的地方：①两类Size的大小应该适当，组件间距设置应该适当。②对于临界点的判断。③切换当前组件时，若间距设置导致部分重叠，应该在动画开始时使用raise()函数将下一个当前组件进行置顶。

        代码有些长就不放在此处了，有兴趣的可以去Qt_Practice中看原型的代码。

        

    * 鼠标点击水波纹效果

        这部分实现思路非常清晰，注意点是路径的构建，绘制应在效果类中的paintEvent里进行，配置应该在主窗体中进行触发。

        相关代码：

        ```c++
        #ifndef RIPPLE_H
        #define RIPPLE_H
        
        #include <QWidget>
        #include <QVariantAnimation>
        #include <QPainter>
        #include <QPainterPath>
        #include <QPoint>
        #include <QCursor>
        
        #define RIPPLE_RADIUS 15
        
        class Ripple : public QWidget
        {
            Q_OBJECT
        public:
            // 构造函数
            explicit Ripple(QWidget *parent = nullptr);
        
            // 重写QWidget的show方法
            void show();
            // 设置水滴颜色
            void setColor(QColor color);
            // 移动水滴到指定位置
            void move(const QPoint &point);
        
        signals:
        private slots:
            // 当水滴半径变化时，更新水滴的绘制
            void onRadiusChanged(QVariant value);
        
        private:
            // 绘制水滴
            void paintEvent(QPaintEvent *event) override;
        
            // 水滴动画
            QVariantAnimation *m_rippleAnimation;
            // 水滴当前半径
            int m_radius;
            // 水滴中心位置
            QPointF m_point;
            // 水滴颜色
            QColor m_color;
            // 显示水滴的路径
            QPainterPath m_showRip;
            // 隐藏水滴的路径
            QPainterPath m_hideRip;
        };
        
        #endif // RIPPLE_H
        
        
        #include "ripple.h"
        #include "qpainter.h"
        
        Ripple::Ripple(QWidget *parent)
            : QWidget{parent}
            , m_rippleAnimation(nullptr)
            , m_radius(0)
            , m_point(QCursor::pos())
            , m_color(QColor(255,120,0,255))
        {
            // 初始化水滴大小和窗口属性
            setFixedSize(RIPPLE_RADIUS*2.5, RIPPLE_RADIUS*2.5);
            setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::CustomizeWindowHint | Qt::Window);
            // 设置窗口背景为透明
            setAttribute(Qt::WA_TranslucentBackground);
            // 关闭窗口时自动删除对象
            setAttribute(Qt::WA_DeleteOnClose, true);
        
            m_rippleAnimation=new QVariantAnimation(this);
        }
        
        void Ripple::show()
        {
            __super::show();
            // 启动水滴动画
            m_rippleAnimation->setStartValue(0);
            m_rippleAnimation->setEndValue(RIPPLE_RADIUS);
            m_rippleAnimation->setDuration(350);
        
            connect(m_rippleAnimation, &QVariantAnimation::valueChanged, this, &Ripple::onRadiusChanged);
            connect(m_rippleAnimation, &QVariantAnimation::finished, this, &Ripple::close);
            // 将水滴颜色的alpha通道设置为250
            m_color.setAlpha(250);
            m_rippleAnimation->start();
        }
        
        void Ripple::setColor(QColor color)
        {
            m_color=color;
        }
        
        void Ripple::move(const QPoint &point)
        {
            QPoint tp=point-QPoint(RIPPLE_RADIUS,RIPPLE_RADIUS);
            __super::move(tp);
        }
        
        void Ripple::onRadiusChanged(QVariant value)
        {
            if (m_radius < RIPPLE_RADIUS)
            {
                // 水滴半径增加2像素
                m_radius += 2;
                // 设置颜色的alpha通道值，使水滴渐渐消失
                m_color.setAlpha(m_color.alpha() - 30);
                // 更新窗口绘制
                update();
            }
        }
        
        void Ripple::paintEvent(QPaintEvent *event)
        {
            // 清空路径
            m_showRip.clear();
            m_hideRip.clear();
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::NoPen);
        
            painter.setBrush(QBrush(m_color));
        
            // 计算水滴显示和隐藏的路径
            m_showRip.addEllipse(QPoint(RIPPLE_RADIUS + 2, RIPPLE_RADIUS + 2), m_radius + 2, m_radius + 2);
            m_hideRip.addEllipse(QPoint(RIPPLE_RADIUS + 2, RIPPLE_RADIUS + 2), m_radius, m_radius);
            m_showRip -= m_hideRip;
        
            // 绘制水滴
            painter.drawPath(m_showRip);
        }
        
        ```

        

        

        

        

    