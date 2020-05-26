#include "arrow.h"
#include <QtMath>

arrow::arrow(QGraphicsObject * parent)
{
    sprite = new QPixmap(":/res/images/Arrow.png");//加载图片
    mtimer = new QTimer(this);//计时
    connect(mtimer, SIGNAL(timeout()), this, SLOT(move()));//子弹随时间移动
    mtimer->start(20);
}

void arrow::move()
{
    Enemy* enemy ;
    //碰撞检测
    enemy= static_cast<Enemy*>(collidingItems().first());
    //撞到了 子弹消失
    if(enemy)
    {
        mtimer->stop();
        mtimer->disconnect();
        delete this;
    }
    //没撞到 旋转角度 跟着
    else
    {
        jiaodu = rotation();
        x = 20 * qCos(qDegreesToRadians(jiaodu));y = 20 * qSin(qDegreesToRadians(jiaodu));
        moveBy(x,y);
    }
}
//画子弹
void arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->setPen(Qt::red);
    painter->drawRect(0, 0, sprite->width(), sprite->height());
}

arrow::~arrow()
{
    delete sprite;//删掉子弹画面
    delete mtimer;//停止调用时间
}
