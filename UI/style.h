#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QColor>

#include <QLabel>
#include <QWidget>

class Style : public QObject
{
    Q_OBJECT
public:
    static Style* getInstance(QObject *parent = nullptr);
    void reset(QMap<QString,QString> style);
    void setLabelStyle(QLabel* label,int imageStyle,int textStyle);
    void setWidgetBackground(QWidget * widget,int imageStyle);

signals:
    void styleChanged();

private:
    explicit Style(QObject *parent = nullptr);
    ~Style();

    static Style* m_instance;

    Style(const Style&) = delete;
    Style& operator=(const Style&) = delete;

    QString   m_styleName;
    QString   m_btnStyle;
    QString   m_backgroundImage1;
    QString   m_backgroundImage2;
    QString   m_backgroundImage3;
    QString   m_backgroundImage4;
    QString   m_labelBorderStyle;
    QString   m_labelBorderRadius;
    QString   m_labelTextStyle1;
    QString   m_labelTextStyle2;
    QString   m_labelTextStyle3;



    QMap <QString,QString> styleDictionary;

};

#endif // STYLE_H
