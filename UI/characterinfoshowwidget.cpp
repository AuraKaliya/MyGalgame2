#include "characterinfoshowwidget.h"

CharacterInfoShowWidget* CharacterInfoShowWidget::m_instance = nullptr;

CharacterInfoShowWidget* CharacterInfoShowWidget::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new CharacterInfoShowWidget();
    }
    return m_instance;
}

CharacterInfoShowWidget::~CharacterInfoShowWidget() {
    m_instance = nullptr;
}

CharacterInfoShowWidget::CharacterInfoShowWidget(QWidget *parent)
    : QWidget{parent}
{

    // 实例化 QVBoxLayout 和 QHBoxLayout
    m_smallVLayout = new QVBoxLayout();
    m_headHLayout = new QHBoxLayout();
    m_mainVLayout = new QVBoxLayout();

    // 实例化 QLabel
    m_headLabel = new QLabel(QString("Head"),this);
    m_IDLabel = new QLabel(QString("ID"),this);
    m_nameLabel = new QLabel(QString("Name"),this);
    m_nicoTitle = new QLabel(QString("NicoTitle"),this);
    m_splitLabel1 = new QLabel(this);
    m_splitLabel2 = new QLabel(this);
    m_splitLabel3 = new QLabel(this);
    m_introdutionLabel = new QLabel(QString("m_introdutionLabel"),this);
    m_LoveInfoLabel = new QLabel(QString("m_LoveInfoLabel"),this);

    backLabel = new QLabel(QString("m_LoveInfoLabel"),this);


    topLabelGroup<<m_IDLabel<<m_nameLabel<<m_nicoTitle;
    splitLabelGroup<<m_splitLabel1<<m_splitLabel2<<m_splitLabel3;

    m_smallVLayout->addWidget(m_IDLabel);
    m_smallVLayout->addWidget(m_nameLabel);
    m_smallVLayout->addWidget(m_nicoTitle);
    m_headHLayout->addWidget(m_headLabel);
    m_headHLayout->addLayout(m_smallVLayout);

    m_mainVLayout->addLayout(m_headHLayout);
    m_mainVLayout->addWidget(m_splitLabel1);
    m_mainVLayout->addWidget(m_introdutionLabel);
    m_mainVLayout->addWidget(m_splitLabel2);
    m_mainVLayout->addWidget(m_LoveInfoLabel);
    m_mainVLayout->addWidget(m_splitLabel3);
    m_mainVLayout->addWidget(backLabel);

    for(auto it:topLabelGroup)
    {
        it->setFixedSize(190,50);


    }
    m_smallVLayout->setSpacing(10);

    m_headLabel->setFixedSize(170,170);
    m_headHLayout->setSpacing(20);

    for(auto it : splitLabelGroup)
    {
        it->setFixedSize(380,20);

        QString pixPath=":/UI/RESOURCE/test_splite1.png";
        //it->setMask(QPixmap(pixPath).mask());
        //it->setPixmap(QPixmap(pixPath));
        it->setStyleSheet("border-image:url("+pixPath+");");

    }
    m_introdutionLabel->setFixedSize(380,230);
    m_LoveInfoLabel->setFixedSize(380,130);
    backLabel->setFixedSize(380,230);
    m_mainVLayout->setSpacing(10);


//    for(auto label:splitLabelGroup)
//    {

//        //label->setMask(QPixmap(pixPath).mask());

//       // label->setStyleSheet("border-image:url("+pixPath+");");
//    }




    setLayout(m_mainVLayout);
    setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency3.png);");
    resize(400,900);
}

void CharacterInfoShowWidget::initCharacterInfomation(Character *character)
{
    m_headLabel->setPixmap(QPixmap(character->headPixPath()).scaled(m_headLabel->size()));

    m_IDLabel->setText("ID:"+QString::number(character->getID()));
    m_nameLabel->setText("姓名:"+character->getName());
    m_nicoTitle->setText("称号:"+character->NicoTitle());

    for(auto label : topLabelGroup)
    {
        Style::getInstance()->setLabelStyle(label,2,2);
        label->setFont(QFont("楷体",15,QFont::Bold,Qt::white));
        label->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);

    }

    m_introdutionLabel->setText("    "+character->getIntroduction());
    m_introdutionLabel->setFont(QFont("楷体",15,QFont::Bold,Qt::white));
    m_introdutionLabel->setAlignment(Qt::AlignLeft);
    m_introdutionLabel->setWordWrap(true);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    m_introdutionLabel->setPalette(pa);   
    Style::getInstance()->setLabelStyle(m_introdutionLabel,2,2);

    m_LoveInfoLabel->setText("");
    m_LoveInfoLabel->setFont(QFont("楷体",15,QFont::Bold,Qt::white));
    m_LoveInfoLabel->setAlignment(Qt::AlignLeft);
    m_LoveInfoLabel->setWordWrap(true);
    QPalette pa2;
    pa2.setColor(QPalette::WindowText,Qt::white);
    m_LoveInfoLabel->setPalette(pa2);
    Style::getInstance()->setLabelStyle(m_LoveInfoLabel,2,2);

}

void CharacterInfoShowWidget::showLoveLines(QString st)
{
    m_LoveInfoLabel->setText(st);
}
