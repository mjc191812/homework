#pragma once

#include <QGraphicsObject>
#include <QTimer>
#include <QPainter>
#include "enemy.h"

class arrow: public QGraphicsObject
{
    Q_OBJECT

public:
   arrow(QGraphicsObject * parent);
    ~arrow();

public slots:
    void move();
private:
    QPixmap * sprite;
    QTimer * mtimer;
    double jiaodu;
    double y;
    double x;
    QRectF boundingRect() const
    {
     return QRectF(0, 0, sprite->width(), sprite->height());
     //float精度的矩形框
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

};
