#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H


#include <QSize>
#include <QPainter>
#include <QString>

class selectButton;
class selectButton2;
class Defend_Tower;
class TowerPosition
{
public:
    TowerPosition(QPoint pos,QString path);//图片的路径
    QPoint getCenterPos();//得到防御塔坑的中心点
    QPoint getPos();//得到防御塔坑的左上点

    bool ContainPos(QPoint pos);//判断pos点是否在防御塔坑的范围内

    void draw(QPainter * painter) const;

    bool hasTower();//判断该防御塔坑内有没有防御塔
    void setHasTower(bool hasTower=true);//设置是否有防御塔

    bool hasButton();//判断该位置有没有button
    void setHasButton(bool hasButton=true);//设置是否有button
    void setButton(selectButton * button);//设置button
    selectButton * getButton();//得到该位置的button

    bool m_hasTowerType[10];//判断是否有某一种塔
    void setHasTower(int i, bool hasTowerType);//设置防御塔
    void containedInTower(int i);//判断是否在某种防御塔选择按钮的点击范围内

    bool hasButton2();//判断该位置有没有button2
    void setHasButton2(bool hasButton2=true);//设置是否有button2
    void setButton2(selectButton2 * button);//设置button2
    selectButton2 * getButton2();//得到该位置的button2

    void setHasUpdate1(bool hasUpdate1);//设置是否有第一次升级
    bool hasUpdate1();

    void setHasUpdate2(bool hasUpdate2);//设置是否有第二次升级
    bool hasUpdate2();

    void setTower(Defend_Tower * tower);
    Defend_Tower * getTower();
    void setRemoveTower();//设置移除防御塔
 private:
    QPoint m_pos;
    QString m_path;

    bool m_hasTower;
    bool m_hasButton;
    static const QSize m_fixedSize;//防御塔坑的固定大小
    static const int m_towerpos[10];//防御塔选择按钮的位置

    selectButton *m_button;

    bool m_hasButton2;
    selectButton2 * m_button2;//私有化button2

    bool m_hasUpdate1;
    bool m_hasUpdate2;

    Defend_Tower *m_tower;//私有化成员Tower
};

#endif // TOWER_POSITION_H
