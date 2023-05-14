#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "sqlitesolve.h"
#include "TOOLS/jssaver.h"
#include "TOOLS/jsreader.h"
#include "DATA/Story/character.h"
#include "TOOLS/musicplayer.h"
#include "UI/SPECIAL/rippleeffect.h"
#include "UI/SPECIAL/ripple.h"
#include "TOOLS/updater.h"
#include "UI/style.h"

#include <QDebug>

#include <QVector>
#include <QPalette>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCursor>

#include <QVBoxLayout>
#include <QTimer>
#include <QKeyEvent>
#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE











class MainWindow : public QStackedWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

   bool	 event(QEvent *event) override;
   void paintEvent(QPaintEvent * event) override;
   void showEvent(QShowEvent *e)override;
   void keyReleaseEvent(QKeyEvent *e) override;
   void updateLastWidget(QWidget*);
   void toMenuWidget();
protected slots:

private:

    Ui::MainWindow *ui;

    QStackedWidget* m_rootWidget;
    QTimer * updateTimer;
    QWidget * m_lastWidget;
    bool paintFlag;
    //DATA检查-更新
    void dataCheck();





};
#endif // MAINWINDOW_H
