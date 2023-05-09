#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sqlitesolve.h"
#include "TOOLS/jssaver.h"
#include "TOOLS/jsreader.h"
#include "DATA/Story/character.h"
#include "TOOLS/musicplayer.h"
#include "UI/SPECIAL/rippleeffect.h"
#include "UI/SPECIAL/ripple.h"
#include "TOOLS/updater.h"

#include <QDebug>

#include <QVector>
#include <QPalette>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCursor>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QTimer>

#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE











class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

   bool	 event(QEvent *event) override;
   void paintEvent(QPaintEvent * event) override;
   void showEvent(QShowEvent *e)override;

protected slots:

private:

    Ui::MainWindow *ui;

    QStackedWidget* m_rootWidget;
    QTimer * updateTimer;
    bool paintFlag;
    //DATA检查-更新
    void dataCheck();





};
#endif // MAINWINDOW_H
