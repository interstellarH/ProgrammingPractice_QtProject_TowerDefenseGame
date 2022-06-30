#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <QPainter>
#include <QString>
#include <QPoint>
#include <QSize>


class MainWindow;

class selectButton
{
public:
    selectButton(QPoint pos,MainWindow * game);
    ~selectButton();

    void draw(QPainter * painter)const;//绘画选择框
    void getRemoved();//选择框被点击了以后，就要被移除
    bool containPos(QPoint pos);//判断鼠标的点击点，是否在选择框的内部
    QPoint getPos();//得到选择框的左上角
private:
    MainWindow * s_game;//指向mainwindow的指针
    QPoint s_pos;//selectButton图片的左上角
    QPixmap s_selectBoxImagePath[10];//储存对应防御塔的图片的路径

    int s_numOfTower[10];//可以选择的防御炮塔的种类,用数字作为编号
    static const QSize m_fixedSize;
};


#endif // SELECTBUTTON_H
