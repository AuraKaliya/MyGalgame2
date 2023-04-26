#include "modelgesture.h"

// 初始化 ModelGesture 类的静态变量 gesture_list 和 gesture_table
QVector<QString> ModelGesture::pose_list = {};
QVector<QVector<QString>> ModelGesture::image_table = {};

void ModelGesture::init(const QVector<QVector<QString> >& table) {
    pose_list.clear();
    image_table.clear();
    // 清空静态变量的内容

    for (const auto& row : table) {
        pose_list.append(row[0]);
        // 将手势名称添加到列表中

        QVector<QString> gesture_images;
        for (int i = 1; i < row.size(); ++i) {
            gesture_images.append(row[i]);
            // 将手势的图片文件名添加到向量中
        }
        image_table.append(gesture_images);
        // 将向量添加到二维列表中，组成 ModelGesture 类的静态数据表
    }
}

ModelGesture::ModelGesture(QString id, QString stand_image_url, QString atk_image_url, QString def_image_url, QString win_image_url, QString lose_image_url)
    : id_(id), stand_image_url_(stand_image_url), atk_image_url_(atk_image_url), def_image_url_(def_image_url), win_image_url_(win_image_url), lose_image_url_(lose_image_url) {}
    // 构造函数的实现，用于创建一个ModelGesture类的实例

QString ModelGesture::getId() const {
    return id_;
}

QString ModelGesture::getStandImageUrl() const {
    return stand_image_url_;
}

QString ModelGesture::getAtkImageUrl() const {
    return atk_image_url_;
}

QString ModelGesture::getDefImageUrl() const {
    return def_image_url_;
}

QString ModelGesture::getWinImageUrl() const {
    return win_image_url_;
}

QString ModelGesture::getLoseImageUrl() const {
    return lose_image_url_;
}
// 读取函数的实现，用于返回实例的属性值


QString ModelGesture::getImageUrlByPose(const QString& pose) const {
    int index = pose_list.indexOf(pose);
    if (index == -1) {
        return "";
        // 如果姿势名称不存在，返回空字符串
    } else {
        return image_table[index][0];
        // 否则返回姿势对应的图片URL
    }
}
// 获取姿势对应的图片URL的函数的实现
