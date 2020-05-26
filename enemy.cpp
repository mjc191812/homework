#include "enemy.h"
Enemy::Enemy(Road nway, int wave)
{
    way=nway;
    distance = 0;
    //加载敌人图片
    sprite = new QPixmap(":/res/images/ax.jpg");
    //随波次增强敌人
    max_hp = 120 + 20*wave;
    //当前血量
    now_hp = max_hp;
    //击杀奖励
    prize = 10;
    //移动速度
    speed = 1000;
    point = 1;
    //安放在起点
    this->setPos(way.getStart().x(), way.getStart().y());
    //走你！
    life = new QTimer();
    connect(life, SIGNAL(timeout()), this, SLOT(move()));
    life->start(20);
}
//死了或者进入重点就停止
void Enemy::stop()
{
    life->stop();
    life->disconnect();
}
void Enemy::damaged(int damage)
{
   now_hp -=damage;

    if(now_hp <= 0 )
    {
        emit dead(prize);
    }
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, sprite->width(), sprite->height());
}

QPainterPath Enemy::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Enemy::Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(*sprite));
    painter->drawRect(0, 0, sprite->width(), sprite->height());
    painter->setBrush(Qt::green);
    painter->drawRect(0, 0, now_hp*sprite->width()/max_hp, 3);
}
void Enemy::move()
{

    if(this->scenePos() != way.getPoints().last())
    {
        distance += (this->scenePos() - way.getPoints()[point]).manhattanLength();

        if(this->scenePos() == way.getPoints()[point]) ++point;
        else
        {
            if(this->scenePos().x() < ((way.getPoints()[point]).x()))
            {
                dx = 1;
            }
            else if (this->scenePos().x() > (way.getPoints()[point].x()))
            {
                dx = -1;
            }
            else
            {
                dx = 0;
            }
            if(this->scenePos().y() < (way.getPoints()[point].y()))
            {
                dy = 1;
            }
            else if (this->scenePos().y() > (way.getPoints()[point].y()))
            {
                dy = -1;
            }
            else
            {
                dy = 0;
            }

            moveBy(dx,dy);
        }
    }
    else
    {
        life->stop();
        life->disconnect();
        emit win();
        delete this;
    }
}


