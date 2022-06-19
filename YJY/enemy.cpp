#include "enemy.h"
#include "waypoint.h"
#include "mainwindow.h"
#include "auxiliary_function.h"
#include "defend_tower.h"

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QVector2D>

const QSize Enemy::e_fixedSize(30,30);//this is a frequently used const,
//adjust it according to the size of pictures

Enemy::Enemy(wayPoint * startPoint, MainWindow * game,const QPixmap & pic):
    QObject(0),
    e_game(game),
    e_pos(startPoint->getPos()),
    e_pic(pic)
{
    e_maxHp=40;
    e_currentHp=e_maxHp;
    e_speed=1;
    e_active=false;
    e_destinationWayPoint=startPoint->getNextWayPoint();
}
Enemy::~Enemy()
{
    e_attackerTowerList.clear();
    e_destinationWayPoint=NULL;
    e_game=NULL;
}
void Enemy::draw(QPainter *painter) const
{
    if(!e_active) return;
    painter->save();
    static const int bloodBarWidth=m_fixedSize.width();
    QPoint bloodBarPoint=e_pos+QPoint(-e_fixedSize.width()/2,-e_fixedSize.height());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect bloodBarBackRect(bloodBarPoint,QSize(bloodBarWidth,2));
    painter->drawRect(bloodBarBackRect);

    painter->setBrush(Qt::green);
    QRect bloodBarRect(bloodBarPoint,QSize((double)bloodBarWidth*e_currentHp/e_maxHp,2));
    painter->drawRect(bloodBarRect);

    QPoint temp(e_pos.x()-e_fixedSize.width()/2,e_pos.y()-e_fixedSize.height()/2);
    painter->drawPixmap(temp.x(),temp.y(),e_pic);
    painter->restore();
}

void Enemy::move()
{
    if(!e_active) return;
    if(collisionWithCircle(e_pos,1,e_destinationWayPoint->getNextWayPoint(),1));//arriving at WayPoint
    {
        if(e_destinationWayPoint->getNextWayPoint()){
            e_pos=e_destinationWayPoint->getPos();
            e_destinationWayPoint=e_destinationWayPoint->getNextWayPoint();
        }
        else {
            e_game->getHpHurted();
            e_game->removeEnemy(this);
            return;
        }
    }
    else//on the road
    {
        QPoint targetPoint=e_destinationWayPoint->getPos();
        double movementSpeed=e_speed;
        QVector2D normalized(targetPoint-e_pos);
        normalized.normalize();
        e_pos=e_pos+normalized.toPoint()*movementSpeed;
    }
}
void Enemy::doActive()
{
    e_active=true;
}
QPoint Enemy::getPos()
{
    return e_pos;
}
void Enemy::getAttacked(Defend_Tower *tower)//被tower攻击
{
    e_attackerTowerList.push_back(tower);
}
void Enemy::getDamaged(int damage)//敌人被攻击受到伤害
{
    e_currentHp-=damage;
    if(e_currentHp<=0){
        e_game->awardGold();
        getRemoved();
    }
}
void Enemy::getRemoved()//当血量非正时，敌人死亡，需要移除
{
    if(e_attackerTowerList.empty()) return;
    else{
        foreach(Defend_Tower * tower, e_attackerTowerList)
            tower->targetKilled();
        e_game->removeEnemy(this);
    }
}

void getLostSight(Defend_Tower * tower)//敌人脱离tower的攻击范围
{
    e_attackerTowerList.removeOne(tower);
}

void getFrozen()//被防御塔定住（修改为减速）
{
    e_speed/=10;
}
void removeFrozen()//解除被定住负面状态
{
    e_speed*=10;
}

void Enemy::reSetHp(int maxHp)
{
    e_maxHp=maxHp;
    e_currentHp=maxHp;
}
void Enemy::reSetSpeed(int times)
{
    e_speed*=times;
}



