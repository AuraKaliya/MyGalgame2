#ifndef CHOICEWIDGET_H
#define CHOICEWIDGET_H

#include <QScrollArea>
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QString>
#include "jumplabel.h"

class ChoiceWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ChoiceWidget(QWidget *parent = nullptr);   
    void initTitleLabel(QLabel* titleLabel,QRect rect);
    void initSlipLabel(QLabel* slipLabel,QRect rect);
    void initChoiceLabel(QVector<JumpLabel*>jumpGroup,QVector<QRect> rectGroup);
    void setIndicatorAvailable(bool flag);
    void setCurrentLabel(JumpLabel* curLabel);
    void initIndicator(QLabel* indicatorLabel,bool right=true);//用于指示当前选择的Label
    void setCurrentLabelPixPath(const QString &newCurrentLabelPixPath);
    void paintEvent(QPaintEvent* e)override;

signals:
private:
    QWidget * m_mainWidget;
    QVector<JumpLabel*>m_jumpLabelGroup;
    QLabel *m_titleLabel;
    QLabel *m_indicatorLabel;
    QLabel *m_slipLabel;
    JumpLabel* m_currentLabel;
    QString m_currentLabelPixPath;
    bool m_indicatorAvailable;
    bool m_indicatorLocationRight;
};

#endif // CHOICEWIDGET_H
