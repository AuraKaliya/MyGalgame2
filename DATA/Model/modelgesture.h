#ifndef MODELGESTURE_H
#define MODELGESTURE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8") // 定义编码格式为UTF-8

class ModelGesture : public ModelBase {
public:
    ModelGesture(){};
    ModelGesture(QString id, QString stand_image_url, QString atk_image_url, QString def_image_url, QString win_image_url, QString lose_image_url);
    // 构造函数，用于创建一个ModelGesture类的实例

    QString getId() const;
    QString getStandImageUrl() const;
    QString getAtkImageUrl() const;
    QString getDefImageUrl() const;
    QString getWinImageUrl() const;
    QString getLoseImageUrl() const;
    // 六个读取函数，返回该实例的id，以及不同动作的图片URL

    static void init(const QVector<QVector<QString> >& table);
    // 初始化函数，用于创建多个ModelGesture类的实例

    QString getImageUrlByPose(const QString& pose) const;
    // 根据姿势名称获取该姿势的图片URL

private:
    static QVector<QString> pose_list;
    static QVector<QVector<QString> > image_table;
    // 静态变量，用于存储多个ModelGesture类的实例的数据表

    QString id_;
    QString stand_image_url_;
    QString atk_image_url_;
    QString def_image_url_;
    QString win_image_url_;
    QString lose_image_url_;
    // 实例变量，存储一个ModelGesture类的实例的数据
};

#endif // MODELGESTURE_H
