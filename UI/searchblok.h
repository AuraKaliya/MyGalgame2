#ifndef SEARCHBLOK_H
#define SEARCHBLOK_H

#include <QWidget>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCompleter>
#include <QString>


class Searchblok : public QLineEdit
{
    Q_OBJECT
public:
    Searchblok(QWidget* prarent=nullptr);

    void initCompleter(QStringList strList);
   // void initCompleter(QVector<QString>strList);
private:
    QCompleter * m_completer;

};

#endif // SEARCHBLOK_H
