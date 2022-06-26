#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QSize>
#include <QPainter>
#include <QString>
#include "selectbutton.h"
#include "defend_tower.h"

class Defend_Tower;

class TowerPosition
{
public:
    TowerPosition(QPoint p, const QPixmap &sprite=(":/new/prefix1/resource1/open_spot.png"));
    QPoint getCenterPos();//获取坑位的中心点
    QPoint getleftPos();//获取坑位的左上点
    int getWidth();
    int getHeight();
    Tower * get_tower();//得到私有成员tower
    selectButton * getButton();//得到私有成员button
    selectButton2 * getButton2();//得到私有成员button2

    bool ContainPos(QPoint pos);//判断某点是否在防御塔坑位的范围内

    void draw(QPainter * painter)const;

    bool hasTower();//判断坑位中是否有防御塔

    void sethasTower(bool hasTower=1);//设置是否有防御塔

    bool hasButton();//判断该位置是否有button
    void setHasButton(bool hasbutton=1);//设置有无button
    selectButton* getButton();
    void setButton(selectButton* x);

    bool hasButton2();//判断该位置是否有button
    void setHasButton2(bool hasbutton=1);//设置有无button
    selectButton* getButton2();
    void setButton2(selectButton* x);

    bool hasTower1();
    void sethasTower1(bool hasTower1=1);
    bool hasTower2();
    void sethasTower2(bool hasTower2=1);
    bool hasTower3();
    void sethasTower3(bool hasTower3=1);

    bool hasUpdate1();
    void sethasUpdate1(bool x);
    bool hasUpdate2();
    void sethasUpdate2(bool x);
    bool m_hasTower;//这里为什么要放在public里面呢
    

private:
    QPoint m_pos;//防御塔坑点位
    QPixmap m_sprite;//图片路径
    
    bool m_hasTower1;//类内定义变量的时候是不可以直接初始化的
    bool m_hasTower2;
    bool m_hasTower3;//是否有塔

    bool m_hasbutton;
    selectButton* m_button;//选择防御塔的按钮
    bool m_hasbutton2;
    selectButton* m_button2;

    bool m_update1;
    bool m_update2;

    Defend_Tower* m_tower;
    static const QSize m_fixedSize;
};

#endif // TOWERPOSITION_H
