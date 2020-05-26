#include "level.h"

Level::Level(Map & _map, QWidget *parent)
{
    map = _map;
    build_curs = nullptr;
    building = false;
    createMap();
}

void Level::createPlace(QPointF point)
{
    TowerPlace * place = new TowerPlace();
    place->setPos(point);
    addItem(place);
}

void Level::createMap()
{
    QVector<QVector<int>> sc_lvl = map.getlvlID();

    lvl_h = map.mapH()*map.getTileH();
    lvl_w = map.mapW()*map.getTileW();

    setSceneRect(0,0, lvl_w, lvl_h);

    for(int i = 0; i < map.mapH(); ++i)
    {
        for (int j =0 ; j < map.mapW(); ++j)
        {
            switch (sc_lvl[i][j])
            {
            case 1 :
            {
                TowerPlace * place = new TowerPlace();
                place->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(place);
                break;
            }
            case 2:
            {
                QGraphicsPixmapItem * sc_obj = new QGraphicsPixmapItem (QPixmap(":/res/images/pink.png"));
                sc_obj->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(sc_obj);
                break;
            }
            case 3:
            {
                QGraphicsPixmapItem * sc_obj = new QGraphicsPixmapItem (QPixmap(":/res/images/hz.jpg"));
                sc_obj->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(sc_obj);
                break;
            }
            case 4:
            {
                QGraphicsPixmapItem * sc_obj = new QGraphicsPixmapItem (QPixmap(":/res/images/hy.jpg"));
                sc_obj->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(sc_obj);
                break;
            }
            case 5:
            {
                QGraphicsPixmapItem * sc_obj = new QGraphicsPixmapItem (QPixmap(":/res/images/hy.jpg"));
                sc_obj->setPos(j*map.getTileW(), i*map.getTileH());
                addItem(sc_obj);
                break;
            }

            }
        }
    }
}

void Level::createTower()
{
    if (build_curs) removeItem(build_curs);
    build_curs = new QGraphicsPixmapItem();
    build_curs->setPixmap(QPixmap(":/res/images/fd.jpg"));
    build_curs->hide();
    addItem(build_curs);
    building = true;
}


void Level::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (build_curs)
    {
        build_curs->show();
        build_curs->setPos(event->scenePos().x()-16,event->scenePos().y()-16 );
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Level::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    TowerPlace * place = dynamic_cast<TowerPlace*>(items(event->scenePos()).last());
    Tower * tow = dynamic_cast<Tower*>(items(event->scenePos()).last());
    clearSelection();
    if(event->button() == Qt::LeftButton)
    {
        if (building && place)
        {
            Tower * tower = new Tower();
            tower->setPos(place->scenePos());
            this->addItem(tower);
            this->removeItem(place);

            this->removeItem(build_curs);
            building = false;

            clearSelection();

            tower->setSelected(true);
            emit setUI(tower);
            emit successBuild(tower->getCost(tower->getLevel()));
       }

        else if (building && !place)
        {
            QGraphicsScene::mousePressEvent(event);
        }
        else if(tow)
        {
            if(!tow->isSelected())
            {
                clearSelection();
                tow->setSelected(true);
                emit setUI(tow);
            }
        }
        else { emit setUI(nullptr);}
    }
    else if (event->button() == Qt::RightButton)
    {
        if (building && build_curs->isVisible())
        {
            clearSelection();
            removeItem(build_curs);
            building = false;
            QGraphicsScene::mousePressEvent(event);
        }
        else {
            QGraphicsScene::mousePressEvent(event);
        }
    }
}

