#ifndef BULLET_H
#define BULLET_H

#include <QPropertyAnimation>
#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QString>
#include <QSize>

class Enemy;
class MainWindow;
class Defend_Tower;
class QGraphicsOpacityEffect;

class Bullet :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ getCurrentPos WRITE setCurrentPos)//子弹动态移动
public:
    Bullet();
    Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,MainWindow * game,
           QString path,int damage = 0, int magical = 0);
    QPoint getCurrentPos();//得到子弹的当前位置
    void setCurrentPos(QPoint pos);//设置子弹的当前位置

    virtual void move();//子弹的移动
    void draw(QPainter * painter)const;//绘画子弹

protected slots:
    virtual void hitTarget();//私有信号槽，击中敌人的时候触发

protected:
    QPoint b_startPos;
    QPoint b_targetPos;
    QPoint b_currentPos;

    QString b_path;
    QList<Enemy *> b_targetEnemy;//与defend_tower种定义一致 第一个位置代表攻击中心点的敌人
                                 //单体攻击则size为1，群体攻击则包含所有可攻击到的目标
    Defend_Tower* b_tower;
    MainWindow * b_game;

    int b_damage = 0;//物理攻击值，与防御塔一致,应该保持在敌人血量的
                     //保证每秒对单个敌人的攻击达到普通敌人血线的50% 预设值在10-50之间
    int b_magical = 0;//魔法攻击值，与防御塔一致
                      //保证每秒对单个敌人的攻击达到普通敌人血线的50% 预设值在10-50之间
    static const QSize m_fixedSize;
};


class Physical_Bullet:public Bullet
{
    Q_OBJECT

public:
    Physical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                    MainWindow * game,QString path);

private:

};


class Magical_Bullet:public Bullet
{
    Q_OBJECT

public:
    Magical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                   MainWindow * game,QString path);

private:

};


class Physical_Explosion:public Bullet
{
    Q_OBJECT
    Q_PROPERTY(int opacity READ getOpacity WRITE setOpacity);

public:
    Physical_Explosion(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                       MainWindow * game,QString path);
    int getOpacity() const;//获得当前图片的透明度
    void setOpacity(int x);//设置图片当前的透明度
    void drawExplosion(QPainter * painter)const;//绘画爆炸效果

private slots:
    void OpacityChanged();//私有槽函数,图片透明度变为0为信号
    virtual void hitTarget();//私有信号槽，击中敌人的时候触发

private:
    int b_range = 0;//攻击范围 代表图片的大小
    QString b_explodePath;//爆炸的图片路径
    int cur_Opacity = 0;//当前的透明度
};

class Frozen_Bullet:public Bullet{
    Q_OBJECT
    Q_PROPERTY(int CurTime READ getCurTime WRITE setTime);

public:
    Frozen_Bullet(QPoint startpos,Defend_Tower* tower,MainWindow * game,QString path,int time);
    virtual void move();//实现冻住的函数
    void draw_Frozen(QPainter * painter)const;//画出冰冻效果

private slots:
    virtual void hitTarget();

private:
    int b_FrozenTime;//定住的时长
    int b_range;//定住的范围
    int b_CurTime = 0;
};
#endif // BULLET_H
