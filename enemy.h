#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include "road.h"
class Enemy: public QGraphicsObject
{
    Q_OBJECT

public:
    Enemy(Road, int wave);//构造函数初始化
    ~Enemy()//删除
    {
        life->stop();
        life->disconnect();
    }

    int getPoint()//取坐标
    {
        return point;
    }
    int getDistance()//取距离
    {
        return distance;
    }
    void damaged(int );
    //以下均为画画用
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public slots:
    void move();
    void stop();
signals:
    void dead(int);
    void win();

private:
    QPixmap * sprite;
    QTimer * life;
    Road way;
    int distance,point,prize;
    int now_hp,max_hp,speed;
    double dy;
    double dx;
};

