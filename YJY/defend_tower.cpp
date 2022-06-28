#include "defend_tower.h"
#include "mainwindow.h"
#include "auxiliary_function.h"
#include "bullet.h"
#include "enemy.h"

#include <QPoint>
#include <QPainter>
#include <QString>
#include <QPixmap>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Defend_Tower::t_picturesize(35,35);

Defend_Tower::Defend_Tower(QPoint pos,MainWindow *game,int type, const QPixmap & sprite )
{
    t_pos=pos;
    t_game=game;
    t_sprite=sprite;
    //初始化属性
    t_type=type;//防御塔类型
    t_attackrange=70;//攻击范围
    t_attacking=0;//是否在攻击
    t_level=1;//防御塔等级
    if(type==1)
    {
        t_damage=10;//防御塔的攻击力
        t_magical=0;//防御塔的破魔属性值
        t_attackGroupRange=0;//群体攻击炮塔的爆炸范围or范围塔的定时范围 单体炮塔此项为0
        t_fireRate=500;//射速or攻击间隔
        t_attacker=NULL;
    }
    else if(type==2)
    {
        t_damage=10;
        t_magical=0.5;
        t_attackGroupRange=0;
        t_fireRate=750;
        t_attacker=NULL;
    }
    else if(type==3)
    {
        t_damage=20;
        t_magical=0;
        t_attackGroupRange=50;
        t_fireRate=1500;
        t_attacker=NULL;
    }
    else if(type==4)
    {
        t_damage=0;
        t_magical=0;
        t_attackGroupRange=50;
        t_fireRate=1500;
        t_attacker=NULL;
    }
    t_fireRateTime=new QTimer(this);
    connect(t_fireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}

Defend_Tower::~Defend_Tower()
{
    delete t_fireRateTime;
    delete t_attacker;
    t_attacker=NULL;
    t_fireRateTime=NULL;
    t_game=NULL;
}

void Defend_Tower::chooseEnemyFromAttack(Enemy* enemy)
{
    t_attacker=enemy;
    AttackEnemy();
    t_attacker->getAttacked(this);
}

void Defend_Tower::AttackEnemy()
{
    t_fireRateTime->start(t_fireRate);
}

void Defend_Tower::shootWeapon()
{

    Bullet* b=new Bullet(t_pos,t_attacker->getPos(),t_damage,t_attacker,t_game,t_magical,t_attackrange);
    b->move();
    t_game->addBullet(b);
}

void Defend_Tower::targetKilled()
{
    if(t_attacker)
    {
        t_attacker=NULL;
    }
    t_fireRateTime->stop();
}

void Defend_Tower::lostSightOfEnemy()
{
    t_attacker->getLostSight(this);
    if(t_attacker!=NULL)
    {
        t_attacker=NULL;
    }
    t_fireRateTime->stop();
}

void Defend_Tower::checkEnemyInRange()
{
    if(t_attacker!=NULL)
    {
        QVector2D normalized(t_attacker->getPos()-t_pos);
        normalized.normalized();
        if(!collisionWithCircle(t_pos,t_attackrange,t_attacker->getPos(),1))
        {
            lostSightOfEnemy();
        }
    }
    else
    {
        QList<Enemy*> enemylist=t_game->getEnemyList;
        QList<Enemy*>::Iterator it=enemylist.begin();
        auto end=enemylist.end();
        while(it!=end)
        {
            if(collisionWithCircle(t_pos,t_attackrange,(*it)->getPos(),1))
            {
                chooseEnemyFromAttack((*it));
                break;
            }
            it++;
        }


    }
}

Enemy* Defend_Tower::getAttackedEnemy()
{
    return t_attacker;
}

void Defend_Tower::draw(QPainter* painter)const
{
    painter->save();
    painter->setPen(Qt::red);//可以采用更漂亮的颜色哦
    painter->drawEllipse(t_pos,t_attackrange,t_attackrange);
    painter->drawText(QRect(this->m_pos.x()-30,this->m_pos.y()+15,100,25),QString("level: %1").arg(m_level));//把防御塔的等级画出来
    painter->drawPixmap(t_pos.x()-t_picturesize.width()/2,t_pos.y()-t_picturesize.height()/2,t_sprite);
}

int Defend_Tower::getDamgae()//得到防御塔的攻击力
{
    return t_damage;
}

void Defend_Tower::levelChange()//防御塔升级
{
    t_level++;
    if(t_type==1)
    {
        t_damage+=10;
        t_attackrange+=30;
        t_fireRate-=50;
    }
    else if(t_type==2)
    {
        t_damage+=10;
        t_attackrange+=30;
        t_magical-=0.2;
        t_fireRate-=50;
    }
    else if(t_type==3)
    {
        t_damage+=10;
        t_attackrange+=30;
        t_attackGroupRange+=20;
        t_fireRate-=150;
    }
    else if(t_type==4)
    {
        t_attackrange+=30;
        t_attackGroupRange+=40;
        t_fireRate-=100;
    }
}
int Defend_Tower::getLevel()//得到防御塔的等级
{
    return t_level;
}

void Defend_Tower::getRemoved()//防御塔被移除
{
    if(t_attacker!=NULL)
    {
        t_attacker->getLostSight(this);
    }
    t_game->removeTower(this);
}

int Defend_Tower::get_attackGroupRange()//获得群体攻击范围
{
    return t_attackGroupRange;
}
