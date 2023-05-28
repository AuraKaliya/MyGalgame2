#ifndef SOURCETABLE_H
#define SOURCETABLE_H

#include <QObject>
#include <QMap>
#include <QString>


class SourceTable : public QObject
{
    Q_OBJECT
public:
    static SourceTable* getInstance();
    ~SourceTable();

    void addInEmblemTable(QString key,QString value);
    QString findEmblemTablePath(QString name);

signals:

private:
    explicit SourceTable(QObject *parent = nullptr);
    static SourceTable* instance;

    QMap<QString,QString>  m_emblemTable;

};

#endif // SOURCETABLE_H
