#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sqlitesolve.h"
#include "TOOLS/jssaver.h"
#include "TOOLS/jsreader.h"
#include "DATA/Story/character.h"
#include "TOOLS/musicplayer.h"



#include <QDebug>

#include <QVector>


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

private:
    Ui::MainWindow *ui;

    //DATA检查-更新
    void dataCheck();





};
#endif // MAINWINDOW_H
