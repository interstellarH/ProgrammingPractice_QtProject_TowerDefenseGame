#ifndef SELECTBUTTON2_H
#define SELECTBUTTON2_H

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSize>

class MainWindow;
class Tower;

class selectButton2
{
public:
    selectButton2(QPoint pos,MainWindow * game);
    ~selectButton2();

    void draw(QPainter * painter)const;//绘画button
    void getRemoved();//移除button2
    Tower * getTower();//得到该button2地防御塔
    void setTower(Tower * tower);//设置该button2地防御塔
    bool containPos(QPoint pos);//判断点击点是否在button2的内部
    QPoint getPos();//得到button2的左上点
private:
    MainWindow * m_game;
    Tower * m_tower;
    QPoint m_pos;
    static const QSize m_fixedSize;
};
#endif // SELECTBUTTON2_H
