#include "towerposition.h"
#include "selectbutton.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_fixedSize(35,35);
TowerPosition::TowerPosition(QPoint pos,QPixmap & sprite):
    m_hasTower(false),
    m_hasTower1(false),
    m_hasTower2(false),
    m_hasTower3(false),
    m_hasButton(false),
    m_hasButton2(false),
    m_pos(pos),
    m_sprite(sprite)
    {}

bool TowerPosition::hasTower()
{
    return m_hasTower;
}

void TowerPosition::sethasTower(bool x)
{
    m_hasTower=x;
}

bool TowerPosition::hasTower1()
{
    return m_hasTower1;
}
void TowerPosition::sethasTower1(bool x)
{
    m_hasTower1=x;
    setHasTower(x);
}

bool TowerPosition::hasTower2()
{
    return m_hasTower2;
}

void TowerPosition::sethasTower2(bool x)
{
    m_hasTower2=x;
    setHasTower(x);
}

bool TowerPosition::hasTower3()
{
    return m_hasTower3;
}

void TowerPosition::sethasTower3(bool x)
{
    m_hasTower3=x;
    setHasTower(x);
}

bool TowerPosition::hasButton()
{
    return m_hasbutton;
}

selectButton* TowerPosition::getButton()
{
    return m_button;
}

void TowerPosition::setButton(selectButton* x)
{
    m_button=x;
}

bool TowerPosition::hasButton2()
{
    return m_hasbutton2;
}

selectButton* TowerPosition::getButton2()
{
    return m_button2;
}

void TowerPosition::setButton2(selectButton* x)
{
    m_button2=x;
}

bool TowerPosition::hasUpdate1()
{
    return m_update1;
}

void TowerPosition::sethasUpdate1(bool x)
{
    m_update1=x;
}

bool TowerPosition::hasUpdate2()
{
    return m_update2;
}

void TowerPosition::sethasUpdate2(bool x)
{
    m_update2=x;
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
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_sprite);
}

void TowerPosition::setRemoveTower()
{
    setTower(NULL);
    setHasTower(false);
    setHasTower1(false);
    setHasTower2(false);
    setHasTower3(false);
    setHasUpdate1(false);
    setHasUpdate2(false);
}
