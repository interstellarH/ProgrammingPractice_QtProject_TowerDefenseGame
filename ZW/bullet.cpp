#include "bullet.h"
#include "defend_tower.h"
#include "mainwindow.h"
#include "auxiliary_function.h"
#include "enemy.h"

#include <QPoint>
#include <QPainter>
#include <QString>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

Bullet::Bullet(){
}

Bullet::Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,MainWindow * game,
              const QPixmap & sprite,int damage,int magical):
               b_startPos(startPos),b_targetPos(targetPos),b_sprite(sprite),
               b_tower(tower),b_game(game),b_damage(damage),b_magical(magical)
{
    b_targetEnemy=tower->getAttackedEnemy();
}

QPoint Bullet::getCurrentPos()
{
    return b_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    b_currentPos = pos;
}

void Bullet::move()
{
    int duration=100;//子弹飞行的时间，经过100ms击中敌人
    QPropertyAnimation * animation=new QPropertyAnimation(this,"b_currentPos");
    animation->setDuration(duration);//设置持续时间
    animation->setStartValue(b_startPos);//设置起始位置
    animation->setEndValue(b_targetPos);//设置目标位置
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));//连接信号槽，击中敌人后，子弹动态运动结束
    animation->start();
}

void Bullet::hitTarget()
{
    if(b_game->getEnemyList().indexOf(b_targetEnemy.front())!=-1)//如果mainwindow的敌人列表中，有子弹击中的这个敌人，该敌人受到相应的伤害
    {
        while(!b_targetEnemy.empty()){//设置物理攻击和魔法攻击的区别
            int harm;
            if(b_damage){
                harm = b_damage-b_targetEnemy.front()->getPhysicalRe();
                b_targetEnemy.front()->getDamaged(harm);
            }
            else{
                harm = b_magical-b_targetEnemy.front()->getMagicalRe();
                b_targetEnemy.front()->getDamaged(harm);
            }
            b_targetEnemy.pop_front();
        }
    }
    b_game->removeBullet(this);//击中敌人后子弹就要消失
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(b_currentPos,b_path);
}

Physical_Bullet::Physical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                                 MainWindow * game,QString path):
                                 Bullet(startPos, targetPos, tower, game, path,
                                        tower->get_damage())
{
}


Magical_Bullet::Magical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                               MainWindow * game,QString path):
                               Bullet(startPos, targetPos, tower, game, path,
                                      0, tower->get_magical())
{
}

Physical_Explosion::Physical_Explosion(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                                       MainWindow * game,QString path):
                                       Bullet(startPos, targetPos, tower, game, path,
                                       tower->get_damage())
{
    b_range=tower->get_attackGroupRange();
}

void Physical_Explosion::hitTarget()
{
    if(b_game->getEnemyList().indexOf(b_targetEnemy.front())!=-1)//如果mainwindow的敌人列表中，有子弹击中的这个敌人，该敌人受到相应的伤害
    {
        while(!b_targetEnemy.empty()){//设置物理攻击和魔法攻击的区别
            int harm;
            if(b_damage){
                harm = b_damage-b_targetEnemy.front()->getPhysicalRe();
                b_targetEnemy.front()->getDamaged(harm);
            }
            else{
                harm = b_magical-b_targetEnemy.front()->getMagicalRe();
                b_targetEnemy.front()->getDamaged(harm);
            }
            b_targetEnemy.pop_front();
        }
    }
    b_game->removeBullet(this);//击中敌人后子弹就要消失
    b_game->addPoint(this,1);//同时将最终运动的位置添加至list1中

    int duration=300;//爆炸效果共持续300ms
    QPropertyAnimation * b_animation=new QPropertyAnimation(this,"cur_Opacity");
    b_animation->setDuration(duration);//设置持续时间
    b_animation->setStartValue(1);//初始透明度为1
    b_animation->setEndValue(0);//终止透明度为0
    connect(b_animation,SIGNAL(finished()),this,SLOT(OpacityChanged()));//连接信号槽，图片消失及后续处理
    b_animation->start();
}

int Physical_Explosion::getOpacity()const{
    return cur_Opacity;
}

void Physical_Explosion::setOpacity(int x){
    cur_Opacity = x;
}

void Physical_Explosion::OpacityChanged(){
    b_game->removePoint(this,1);//将最终运动的位置移除list1
}

void Physical_Explosion::drawExplosion(QPainter *painter)const{
    painter->setOpacity(cur_Opacity);
    painter->drawPixmap(b_targetPos,b_explodePath);
}

Frozen_Bullet::Frozen_Bullet(QPoint startpos,Defend_Tower* tower,MainWindow * game,QString path,int time):
    Bullet(startpos,QPoint(NULL,NULL),tower,game,path){
    b_FrozenTime = time;
    b_range = tower->get_attackGroupRange();
}

void Frozen_Bullet::move(){
    QPropertyAnimation * animation=new QPropertyAnimation(this,"b_CurTime");
    animation->setDuration(b_FrozenTime);//设置持续时间
    animation->setStartValue(0);//设置起始时间
    animation->setEndValue(b_FrozenTime);//设置终止时间
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));//连接信号槽，时间结束后动画结束
    animation->start();
    b_game->addPoint(this,2);
}

void Frozen_Bullet::draw_Frozen(QPainter * painter)const{
    foreach(Enemy* enemy, b_targetEnemy){
        painter->drawPixmap(enemy->getPos(),b_path);//在被冻住的敌人位置画上效果（贴上冻图）
    }

    painter->setPen(QColor(177,220,245));//设置画笔颜色
    int x=b_startPos.x(),y=b_startPos.y();//圆心的位置 修正一下，这里是rect左上角点的坐标
    int r1 = (double)(b_CurTime%1000)/1000.0*b_range;//三个圆圈形成波浪的效果呈现范围
    int r2 = (double)((b_CurTime-333)%1000)/1000.0*b_range;
    int r3 = (double)((b_CurTime-667)%1000)/1000.0*b_range;
    QRectF rect1(x,y,r1,r1);
    painter->drawEllipse(rect1);
    if(b_CurTime>333){
        QRectF rect2(x,y,r2,r2);
        painter->drawEllipse(rect2);
    }
    if(b_CurTime>667){
        QRectF rect3(x,y,r3,r3);
        painter->drawEllipse(rect3);
    }
}

void Frozen_Bullet::hitTarget(){
    b_game->removePoint(this,2);
}
