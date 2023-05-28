#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::MainWindow)
{

    //ui->setupUi(this);

    //paintFlag=false;

    /**timer和更新器**//**timer和更新器**//**timer和更新器**//**timer和更新器**/
    updateTimer=new QTimer(this);
    updateTimer->setInterval(33);
    connect(updateTimer,&QTimer::timeout,this,[=](){
        Updater::getInstance()->updateJumpLabel();
    });
    updateTimer->start();
    /**timer和更新器**//**timer和更新器**//**timer和更新器**//**timer和更新器**/

    // this->setStyleSheet("background-color:black;");
    //setWindowFlags(Qt::FramelessWindowHint);

    /**对主窗体的样式设置**//**对主窗体的样式设置**//**对主窗体的样式设置**//**对主窗体的样式设置**/
    //setStatusBar(nullptr);
    setFixedSize(1600,900);
    /**对主窗体的样式设置**//**对主窗体的样式设置**//**对主窗体的样式设置**//**对主窗体的样式设置**/


    /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/
    MenuWidget::getInstance(this);
    MenuWidget::getInstance()->resize(1600,900);
    MenuWidget::getInstance()->move(0,0);
    MenuWidget::getInstance()->setWindowFlags(Qt::FramelessWindowHint);
    MenuWidget::getInstance()->setVisible(true);
     /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/ /**实例化菜单窗体**/

    /**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**/
    SettingWidget::getInstance(this);
    SettingWidget::getInstance()->resize(1600,900);
    SettingWidget::getInstance()->move(0,0);
    SettingWidget::getInstance()->setWindowFlags(Qt::FramelessWindowHint);
    SettingWidget::getInstance()->setVisible(true);
    /**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**//**实例化设置窗体**/

    /**实例化存读窗体**//**实例化存读窗体**//**实例化存读窗体**//**实例化存读窗体**//**实例化存读窗体**/
    RSWidget::getInstance(this);
    RSWidget::getInstance()->resize(1600,900);
    RSWidget::getInstance()->move(0,0);
    RSWidget::getInstance()->setWindowFlags(Qt::FramelessWindowHint);
    RSWidget::getInstance()->setVisible(true);
    /**实例化存读窗体**//**实例化存读窗体**//**实例化存读窗体**//**实例化存读窗体**/

    /**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**/
    MainWidget::getInstance(this);
    MainWidget::getInstance()->resize(1600,900);
    MainWidget::getInstance()->move(0,0);
    MainWidget::getInstance()->setWindowFlags(Qt::FramelessWindowHint);
    MainWidget::getInstance()->setVisible(true);


    /**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**//**实例化主界面窗体**/


   /**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**/
    CharacterWidget::getInstance(this);
    CharacterWidget::getInstance()->resize(1600,900);
    CharacterWidget::getInstance()->move(0,0);
    CharacterWidget::getInstance()->setWindowFlags(Qt::FramelessWindowHint);
    CharacterWidget::getInstance()->setVisible(true);
   /**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**//**实例化角色界面窗体**/





    Style::getInstance();
    CharacterHub::getInstance();

    addWidget(MenuWidget::getInstance());
    addWidget(SettingWidget::getInstance());
    addWidget(RSWidget::getInstance());
    addWidget( MainWidget::getInstance());
    addWidget(CharacterWidget::getInstance());

    Updater::getInstance()->registerWidget("设置",SettingWidget::getInstance());
    Updater::getInstance()->registerParent(SettingWidget::getInstance(),this);

    Updater::getInstance()->registerWidget("读取",RSWidget::getInstance());
    Updater::getInstance()->registerParent(RSWidget::getInstance(),this);

    Updater::getInstance()->registerWidget("启航",MainWidget::getInstance());
    Updater::getInstance()->registerParent(MainWidget::getInstance(),this);

    Updater::getInstance()->registerWidget("角色一览",CharacterWidget::getInstance());
    Updater::getInstance()->registerParent(CharacterWidget::getInstance(),this);



//    m_rootWidget=new QStackedWidget(this->centralWidget());
//    m_rootWidget->setFixedSize(1600,900);
//    m_rootWidget->move(0,0);

//    QVBoxLayout *layout = new QVBoxLayout(this->centralWidget());
//    layout->addWidget(m_rootWidget);


//    m_rootWidget->addWidget(MenuWidget::getInstance());
//    m_rootWidget->setCurrentWidget(MenuWidget::getInstance());
//    m_rootWidget->currentWidget()->setWindowFlags(Qt::FramelessWindowHint);



  //  SQLiteSolve::instance();


               /**测试：sqlitesolve能否正常使用   ---可以正常使用**/
//QString sqe("DELETE FROM CardInformation WHERE 1=1;");
//QString sq("create table CardInformation(ID integer primary key,Name Text,MainCategory text,SecondCategory text,Rarity text,Introduction text,TachieImageUrl text);");

//QString sq2("insert into CardInformation(ID,Name,MainCategory,SecondCategory,Rarity,Introduction,TachieImageUrl) values (10001,'李韶奏','角色','角色','SSR','幻想而生的少女，拥有谜一样的背景。','qrc:/Character/RESOURCE/head_LiShaoZou.jpg');");
//    qDebug()<<"sq:"<<sq<<endl;
//    SQLiteSolve::instance().executeSql(sqe);
//    SQLiteSolve::instance().executeSql(sq);
//    SQLiteSolve::instance().addRecord(QString("CardInformation"),QString("10002|'锋'|'角色'|'角色'|'SSR'|'主角'|'0'"));
//    qDebug()<<SQLiteSolve::instance().selectRecord(QString("CardInformation"));
//    SQLiteSolve::instance().executeSql(sq2);
//    qDebug()<<SQLiteSolve::instance().selectRecord(QString("CardInformation"))<<endl;
//    qDebug()<<"SQL:"<<SQLiteSolve::instance().executeSql("SELECT * from CardInformation;");
                /**测试：sqlitesolve能否正常使用   ---可以正常使用**/




    /**测试：关于存档功能能否正常使用   ---可以正常使用**/
//    QString path("F:\\QTF\\myGalgame4\\RESOURCE\\Achievement1.json");
//    qDebug()<<path;
//    JSSaver Saver1;
//    JSReader Reader1;
//    Reader1.init();
//    Reader1.setFilePath(path);
//    Reader1.readJsonFileToAchievement();

//    Saver1.init();
//    Saver1.setFilePath(path);
//    Saver1.saveAchievementToJsonFile();

 /**测试：关于存档功能能否正常使用   ---可以正常使用**/



 /**测试：关于人物信息读取功能能否正常使用   ---可以正常使用**/
//     QString path("F:\\QTF\\myGalgame4\\RESOURCE\\Character1.json");
//     qDebug()<<path;
//     JSReader Reader1;
//     Reader1.init();
//     Reader1.setFilePath(path);
//     QVector<Character*> test1;
//     test1=Reader1.readJsonFileToCharacter();

//     for(int i=0;i<test1.size();i++)
//         test1[i]->show();
 /**测试：关于人物信息读取功能能否正常使用   ---可以正常使用**/





    /*

      name: test_music1 src: :/Music/RESOURCE/test_music1.mp3
      name: test_music2 src: :/Music/RESOURCE/test_music2.mp3

     */

/**测试：关于音乐播放功能能否正常使用   ---可以正常使用**/
//QString path("F:\\QTF\\myGalgame4\\RESOURCE\\Music1.json");
// qDebug()<<path;

//    JSReader Reader1;
//     Reader1.init();
//    Reader1.setFilePath(path);
//    Reader1.readJsonFileToMusicPlayer();
//    MusicPlayer::getInstance()->setNowMusic(QString("test_music2"));

/**测试：关于音乐播放功能能否正常使用   ---可以正常使用**/


//    QGraphicsScene * scene =new QGraphicsScene(this);
//    QGraphicsView *graphicsView=new QGraphicsView(this);
//    graphicsView->resize(width(),height());
//    graphicsView->setScene(scene);

//    QPointF center(graphicsView->width() / 2, graphicsView->height() / 2);
//    QRgb color = qRgb(0, 162, 232);
//    RippleEffect* ripple = new RippleEffect(center, color, 20.0);
//    scene->addItem(ripple);

    //connect(this, &QWidget::clicked, ripple, &RippleEffect::mousePressEvent); // 将点击信号连接到槽函数



   // 创建RippleEffect对象
    //connect(this,SIGNAL(mousePressEvent), this, SLOT(pressevent(QMouseEvent *event)));


////载入数据////载入数据////载入数据////载入数据////载入数据////载入数据////载入数据////载入数据

    QString path1="D:\\QTF\\myGalgame4\\RESOURCE\\";
///
    JSReader Reader1;
    Reader1.init();


///





/// Style数据
    QString path(path1+"Style.json");
    Reader1.setFilePath(path);
    Reader1.readJsonFileToStyle();


///
    path=QString(path1+"Character1.json");
    Reader1.setFilePath(path);
    CharacterHub::getInstance()->initCharaHub(Reader1.readJsonFileToCharacter());
    CharacterHub::getInstance()->show();

/// MenuWidget页面数据
    path=QString(path1+"MenuWidgetSetting.json");
    Reader1.setFilePath(path);
    Reader1.readJsonFileToMenuWidget();


    // 测试setting ---√
/// SettingWidget页面数据
     path=QString(path1+"SettingWidget.json");
     Reader1.setFilePath(path);
     Reader1.readJsonFileToSetting();


     //测试存读档  ---√
     path=QString(path1+"Achievement_ALL.json");
     Reader1.setFilePath(path);
     Reader1.readJsonFileToReadAndSave();

    //测试MainWidget页面数据
     path=QString(path1+"MainWidget.json");
     Reader1.setFilePath(path);
     Reader1.readJsonFileToMainWidget();

    //测试CharacterWidget页面数据
     path=QString(path1+"CharacterWidget.json");
     Reader1.setFilePath(path);
     Reader1.readJsonFileToCharacterWidget();



////载入数据////载入数据////载入数据////载入数据////载入数据////载入数据////载入数据


  setCurrentWidget(MenuWidget::getInstance());





  //test-----页面

  StoryInfoWidget * stInfo=new StoryInfoWidget();
  stInfo->initTachie(CharacterHub::getInstance()->findCharacter(10002),QRect(0,0,360,640));
  stInfo->initStory(CharacterHub::getInstance()->findCharacter(10002)->storyTitle(),CharacterHub::getInstance()->findCharacter(10002)->story());

  stInfo->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::event(QEvent *event)
{

    if(event->type()==QEvent::MouseButtonPress)
    {
        //在鼠标点击位置展示水波纹效果
        qDebug()<<"RIPPLE";
        Ripple *rip=new Ripple;
        rip->move(QCursor::pos());
        rip->setColor(QColor(255,120,0,255));
        rip->show();

    }


//
//    Updater::getInstance()->updateJumpLabel();
//    this->setAttribute(Qt::WA_Mapped);
//    QSize oldSize=this->size();
//    resize(oldSize+QSize(10,10));
//    update();
//    resize(oldSize);


     //QCoreApplication::processEvents();
    return QStackedWidget::event(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    Updater::getInstance()->updateJumpLabel();
//     for(auto it: Updater::getInstance()->jumpGroup)
//        it->setPixmap(*it->m_PressPix);


}

void MainWindow::showEvent(QShowEvent *e)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(e);

//        QSize oldSize=this->size();
//        resize(oldSize+QSize(10,10));
//        update();
//        resize(oldSize);


}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_Q)
    {
        toMenuWidget();
    }

}

void MainWindow::updateLastWidget(QWidget *w)
{
    m_lastWidget=w;
}

void MainWindow::toMenuWidget()
{
    this->setCurrentWidget(MenuWidget::getInstance());
}

