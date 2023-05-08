#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  this->setStyleSheet("background-color:black;");
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








}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::event(QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        qDebug()<<"PRESS!!";
        Ripple *rip=new Ripple;
        rip->move(QCursor::pos());
        rip->setColor(QColor(255,120,0,255));

        rip->show();
    }
    return true;
}

