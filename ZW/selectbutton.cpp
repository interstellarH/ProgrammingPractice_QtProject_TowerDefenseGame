#include "selectbutton.h"
#include "mainwindow.h"

const QSize selectButton::m_fixedSize(105,35);

selectButton::selectButton(QPoint pos,MainWindow * game):
    s_game(game),
    s_pos(pos)
{
    //三张图片的路径信息
    s_selectBoxImagePath[0]=":/images/tower1.jpg";
    s_selectBoxImagePath[1]=":/images/tower2.png";
    s_selectBoxImagePath[2]=":/images/tower3.png";
    s_selectBoxImagePath[3]=":/images/tower4.png";
}

selectButton::~selectButton()
{
    s_game=NULL;
}

void selectButton::draw(QPainter *painter) const
{
    painter->save();
    painter->drawPixmap(s_pos.x(),s_pos.y(),s_selectBoxImagePath[0]);
    painter->drawPixmap(s_pos.x()+70,s_pos.y(),s_selectBoxImagePath[1]);
    painter->drawPixmap(s_pos.x(),s_pos.y()+70,s_selectBoxImagePath[2]);
    painter->drawPixmap(s_pos.x()+70,s_pos.y()+70,s_selectBoxImagePath[3]);
    painter->restore();
}

void selectButton::getRemoved()
{
    s_game->removeButton(this);
}

bool selectButton::containPos(QPoint pos)
{
    bool xInhere=pos.x()>s_pos.x() && pos.x()<s_pos.x()+m_fixedSize.width();
    bool yInhere=pos.y()>s_pos.y() && pos.y()<s_pos.y()+m_fixedSize.height();
    return xInhere && yInhere;
}

QPoint selectButton::getPos()
{
    return this->s_pos;
}
