#include "selectbutton.h"
#include "mainwindow.h"

const QSize selectButton::m_fixedSize(140,35);//这个是在containPos里面用到，如果是四张图的话，长度不是105
//不过这里还要考虑到图片大小呀，咱们的图片不一定都是35*35的，所以后期可以再改
selectButton::selectButton(QPoint pos,MainWindow * game):
    s_game(game),
    s_pos(pos)
{
    //四种塔的图片路径信息
    s_selectBoxImagePath[0]=":/new/prefix1/resource1/T1.png";
    s_selectBoxImagePath[1]=":/new/prefix1/resource1/T2.png";
    s_selectBoxImagePath[2]=":/new/prefix1/resource1/T3.png";
    s_selectBoxImagePath[3]=":/new/prefix1/resource1/T4.png";
}

selectButton::~selectButton()
{
    s_game=NULL;
}

void selectButton::draw(QPainter *painter) const
{
    painter->save();
    painter->drawPixmap(s_pos.x(),s_pos.y(),s_selectBoxImagePath[0]);//改成排在一条直线上了
    painter->drawPixmap(s_pos.x()+35,s_pos.y(),s_selectBoxImagePath[1]);
    painter->drawPixmap(s_pos.x()+70,s_pos.y(),s_selectBoxImagePath[2]);
    painter->drawPixmap(s_pos.x()+105,s_pos.y(),s_selectBoxImagePath[3]);
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
