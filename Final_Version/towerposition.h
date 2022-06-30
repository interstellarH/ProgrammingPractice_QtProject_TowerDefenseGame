#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QSize>
#include <QPainter>
#include <QString>
#include "selectbutton.h"
#include "selectbutton2.h"
#include <QPoint>
class Defend_Tower;

class TowerPosition
{
public:
    //TowerPosition(QPoint p, const QPixmap &sprite);
    TowerPosition(QPoint p);
    QPoint getCenterPos();//获取坑位的中心点
    QPoint getleftPos();//获取坑位的左上点
    int getWidth();
    int getHeight();
    Defend_Tower * get_tower();//得到私有成员tower

    bool ContainPos(QPoint pos);//判断某点是否在防御塔坑位的范围内

    void draw(QPainter * painter)const;

    bool hasTower();//判断坑位中是否有防御塔

    void sethasTower(bool hasTower=1);//设置是否有防御塔

    void setTower(Defend_Tower* tower);//设置防御塔

    bool hasButton();//判断该位置是否有button
    void setHasButton(bool hasbutton=1);//设置有无button
    selectButton* getButton();
    void setButton(selectButton* x);

    bool hasButton2();//判断该位置是否有button
    void setHasButton2(bool hasbutton=1);//设置有无button
    selectButton2* getButton2();
    void setButton2(selectButton2* x);

    bool hasTowers(int i);
    void sethasTowers(int i, bool x=1);

    bool hasUpdate1();
    void sethasUpdate1(bool x);
    bool hasUpdate2();
    void sethasUpdate2(bool x);
    bool m_hasTower;//这里为什么要放在public里面呢

    void setRemoveTower();//移除防御塔

    QPoint getPos();

private:
    QPoint m_pos;//防御塔坑点位
    QPixmap m_sprite;//图片路径

    bool m_hasTowers[5];//类内定义变量的时候是不可以直接初始化的

    bool m_hasbutton;
    selectButton* m_button;//选择防御塔的按钮
    bool m_hasbutton2;
    selectButton2* m_button2;

    bool m_update1;
    bool m_update2;

    Defend_Tower* m_tower;
    static const QSize m_fixedSize;
};

#endif // TOWERPOSITION_H
