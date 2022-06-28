#ifndef AUXILIARY_FUNCTION_H
#define AUXILIARY_FUNCTION_H
#include <QPoint>
#include <cmath>

inline bool collisionWithCircle(QPoint p1,int r1,QPoint p2,int r2)
{//在h文件内部实现函数
    int xx=p1.x()-p2.x();
    int yy=p1.y()-p2.y();
    int dis=sqrt(xx*xx+yy*yy);
    if(dis<r1+r2)
    {
        return true;
    }
    return false;
}
#endif // AUXILIARY_FUNCTION_H
