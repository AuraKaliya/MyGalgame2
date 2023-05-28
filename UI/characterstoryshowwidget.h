#ifndef CHARACTERSTORYSHOWWIDGET_H
#define CHARACTERSTORYSHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include  "style.h"

class CharacterStoryShowWidget : public QWidget
{
    Q_OBJECT

public:
    static CharacterStoryShowWidget* getInstance(QWidget *parent = nullptr);
    void initCharacterStory(QString tiltle,QString story);
    ~CharacterStoryShowWidget();

private:
    QLabel *m_titleLabel;
    QLabel *m_storyLabel;
    explicit CharacterStoryShowWidget(QWidget *parent = nullptr);
    static CharacterStoryShowWidget* instance;
};

#endif // CHARACTERSTORYSHOWWIDGET_H
