#include "mainwindow.h"

#include <QApplication>

//#include "UI/characterinfoshowwidget.h"
//#include "UI/characterhubwidget.h"
#include "UI/carouselmapwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    CharacterInfoShowWidget s;
//    s.show();

//    CharacterHubWidget s2;
//    s2.show();

    CarouselMapWidget w2;
    w2.initTest();

   // w2.initMaskTest();
    w2.show();
   // w2.preLabel();
   // w2.preLabel();
  // w2.nextLabel();
    return a.exec();
}
