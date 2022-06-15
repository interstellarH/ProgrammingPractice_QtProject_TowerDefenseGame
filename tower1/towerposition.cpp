#include "towerposition.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_fixedSize(35,35);
TowerPosition::TowerPosition(QPoint pos,QString path)
{
    m_pos=pos;
    m_path=path;
    m_hasTower=0;
}

bool TowerPosition::hasTower()
{
    return m_hasTower;
}

QPoint TowerPosition::getCenterPos()
{
    QPoint temp;
    temp.setX(m_pos.x()+m_fixedSize.width()/2);
    temp.setY(m_pos.y()+m_fixedSize.height()/2);
    return temp;
}

QPoint TowerPosition::getleftPos()
{
    return m_pos;
}

bool TowerPosition::ContainPos(QPoint pos)
{
    if(pos.x()>m_pos.x()&&pos.y()>m_pos.y())
    {
        if(pos.x()<m_pos.x()+m_fixedSize.width()&&pos.y()<m_pos.y()+m_fixedSize.height())
        {
            return 1;
        }
    }
    return 0;
}

void TowerPosition::draw(QPainter* painter)const
{
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_path);
}
