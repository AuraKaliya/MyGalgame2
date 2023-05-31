#include "style.h"

Style* Style::m_instance = nullptr;

Style::Style(QObject *parent) : QObject(parent),
    m_styleName(""),
    m_btnStyle(""),
    m_backgroundImage1(""),
    m_backgroundImage2(""),
    m_backgroundImage3(""),
    m_backgroundImage4(""),
    m_labelBorderStyle(""),
    m_labelBorderRadius(""),
    m_labelTextStyle1(""),
    m_labelTextStyle2(""),
    m_labelTextStyle3("")
{

}

Style::~Style()
{

}

Style* Style::getInstance(QObject *parent)
{
    if (m_instance == nullptr)
    {
        m_instance = new Style(parent);
    }

    return m_instance;
}

void Style::reset(QMap<QString, QString> style)
{
    m_styleName = style["StyleName"];
    m_backgroundImage1 = style["background_image1"];
    m_backgroundImage2 = style["background_image2"];
    m_backgroundImage3 = style["background_image3"];
    m_backgroundImage4 = style["background_image4"];
    m_labelBorderStyle = style["Label_border_style"];
    m_labelBorderRadius = style["Label_border_radius"];
    m_labelTextStyle1 = style["Label_text_style1"];
    m_labelTextStyle2 = style["Label_text_style2"];
    m_labelTextStyle3 = style["Label_text_style3"];

    styleDictionary=style;
    emit styleChanged();
}

void Style::setLabelStyle(QLabel *label, int imageStyle, int textStyle)
{

    QString styleSheet="";

    styleSheet+=styleDictionary.value(QString("background_image"+QString::number(imageStyle)));
    styleSheet+=styleDictionary.value(QString("Label_text_style"+QString::number(textStyle)));

    styleSheet+=m_labelBorderStyle;
    styleSheet+=m_labelBorderRadius;
    qDebug()<<styleSheet;
    label->setStyleSheet(styleSheet);
}

void Style::setWidgetBackground(QWidget *widget, int imageStyle)
{
    widget->setWindowFlags(Qt::FramelessWindowHint);
    QString styleSheet="";
    styleSheet+=styleDictionary.value(QString("background_image"+QString::number(imageStyle)));
    styleSheet+=m_labelBorderRadius;
    qDebug()<<styleSheet;
    widget->setStyleSheet(styleSheet);
}

void Style::setLabelStyleByPalete_45_white(QLabel *label)
{
        label->setFont(QFont("楷体",45,QFont::Bold,Qt::white));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);




}

void Style::setLabelStyleByPalete_25_white(QLabel *label)
{
        label->setFont(QFont("楷体",25,QFont::Bold,Qt::white));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pa);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
}
