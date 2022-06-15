#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QSize>
#include <QPainter>
#include <QString>

class TowerPosition
{
public:
    TowerPosition(QPoint p,QString path=(":/new/prefix1/resource1/open_spot.png"));
    QPoint getCenterPos();//获取坑位的中心点
    QPoint getleftPos();//获取坑位的左上点

    bool ContainPos(QPoint pos);//判断某点是否在防御塔坑位的范围内

    void draw(QPainter * painter)const;

    bool hasTower();//判断坑位中是否有防御塔

    void sethasTower(bool hasTower=1);//设置是否有防御塔

private:
    QPoint m_pos;
    QString m_path;
    bool m_hasTower;
    static const QSize m_fixedSize;
};

#endif // TOWERPOSITION_H
