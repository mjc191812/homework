#include "game.h"
#include <QtGlobal>
#include<QTime>
#include<QDebug>
Game::Game(QWidget *parent)
{
    //设置背景图片//
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));          //设置随机数种子
        int rand = qrand() % 3;   QPalette pal;
      if(rand==0)
      {
          pal.setBrush(this->backgroundRole(), QBrush(QImage(":/res/images/bj1.jpg")));
          this->setPalette(pal);
          this->setAutoFillBackground(true);
      }
      else if(rand==1)
      {

          pal.setBrush(this->backgroundRole(), QBrush(QImage(":/res/images/bj2.jpg")));
          this->setPalette(pal);
          this->setAutoFillBackground(true);
      }
      else
      {

          pal.setBrush(this->backgroundRole(), QBrush(QImage(":/res/images/bj3.jpg")));
          this->setPalette(pal);
          this->setAutoFillBackground(true);
      }
    //********************//



    adjustSize();
    setWindowTitle("辉夜大小姐想让我表白，单身狗的反击大作战");

    //设置背景音乐//
    QMediaPlaylist *playlist = new QMediaPlaylist();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    rand=qrand()%3;
    playlist->addMedia(QUrl("qrc:/res/music/atoe.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer(this);
    music->setPlaylist(playlist);
    music->setVolume(25);
    music->play();

    //****Initialisation****//
    parser = new LevelParser(":/res/maps/map.tmx");
    towerUI = new TowerUI(this);
    hud = new HUD(this);

    road = parser->getRoad();
    level = new Level(parser->getMap(), this);

    waves = {10, 15};

    selectedTower = nullptr;
    wave = 0;
    enemies = waves[0];
    currentEnemy = 0;
    life = 10;
    money = 100;
    //********************//


    //****SIGNALS****//
    connect(this, SIGNAL(ch_money(int)), &build_ui, SLOT(setPossible(int)));
    connect(this, SIGNAL(ch_money(int)), towerUI, SLOT(setMoney(int)));
    connect(level,SIGNAL(setUI(Tower*)), this, SLOT(selectTower(Tower*)));
    connect(level, SIGNAL(successBuild(int)), this, SLOT(reduceMoney(int)));
    connect(&build_ui, SIGNAL(build()), level, SLOT(createTower()));

    emit ch_enemy(enemies);
    emit ch_life(life);
    emit ch_money(money);
    emit ch_wave(wave);
    //********************//

    //****View****//
    QGraphicsView * q = new QGraphicsView(this);
    q->setScene(level);
    q->setMouseTracking(true);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setRenderHint(QPainter::Antialiasing, false);
    //********************//

    //****Layout****//
    QVBoxLayout * v_box = new QVBoxLayout();
    QHBoxLayout * h_box = new QHBoxLayout();

    h_box->addLayout(v_box);
    v_box->addWidget(hud);
    v_box->addWidget(towerUI);
    h_box->setSizeConstraint(QLayout::SetFixedSize);
    h_box->addWidget(q);
    h_box->addWidget(&build_ui);
    v_box->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(h_box);
    //********************//
}

void Game::gameOver()
{

    QMessageBox * restart = new QMessageBox (QMessageBox::Question,"游戏失败","重新开始?", QMessageBox::Yes| QMessageBox::No);
    music->stop();
    spawnTimer->stop();
    spawnTimer->disconnect();

    emit stopEnemy();

    int choice = restart->exec();

    if(choice == QMessageBox::Yes)
    {
        Game * game  = new Game();
        this->close();
        game->show();
    }
    else
    {
        close();
    }
}

void Game::win()
{
    QMessageBox * restart = new QMessageBox (QMessageBox::Question, "游戏胜利","下一关?", QMessageBox::Yes| QMessageBox::No);
    music->stop();
    int choice = restart->exec();

    if(choice == QMessageBox::Yes)
    {
        this->close();
        Game * game  = new Game();
        game->show();
    }
    else
    {
        close();
    }
}

void Game::wasteLife()
{
    --life;
    --enemies;

    if(enemies == 0)
    {
        waves.pop_front();

        if (!waves.empty())
        {
            ++wave;
            enemies = waves[0];
            emit ch_wave(wave);
            emit btn_wave(true);
        }
        else win();
    }
    if (life <= 0  ) gameOver();

    emit ch_life(life);
    emit ch_enemy(enemies);

}

void Game::reduceMoney(int cash)
{
    money-=cash;
    emit ch_money(money);
}

void Game::selectTower(Tower * tower)
{
    selectedTower = tower;
    towerUI->setUi(selectedTower);
}

void Game::upgradeTower()
{
    money-=selectedTower->getCost(selectedTower->getLevel());
    selectedTower->upgrade();
    emit ch_money(money);
}

void Game::cellTower()
{
    if(selectedTower)
    {
        money+=selectedTower->getCost(selectedTower->getLevel())/2;
        level->createPlace(selectedTower->scenePos());
        emit ch_money(money);
        level->clearSelection();
        level->removeItem(selectedTower);
        delete selectedTower;
        selectedTower = nullptr;
        towerUI->setUi();
    }
}

void Game::createEnemies()
{
    emit btn_wave(false);
    spawnTimer = new  QTimer();
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnTimer->start(1000);
}

void Game::spawnEnemy()
{
    Enemy * enemy = new Enemy(road, wave);
    level->addItem(enemy);
    ++currentEnemy;

    connect(this, SIGNAL(stopEnemy()), enemy, SLOT(stop()));
    connect(enemy, SIGNAL(win()), this, SLOT(wasteLife()));
    connect(enemy, SIGNAL(dead(int)), this, SLOT(killEnemy(int)));

    if (currentEnemy == waves[0])
    {
        spawnTimer->disconnect();
        currentEnemy = 0;
    }
}

void Game::lootEnemy(int prize)
{
    money += prize;
    --enemies;

    if(enemies == 0)
    {
        waves.pop_front();

        if (!waves.empty())
        {
            ++wave;
            enemies = waves[0];
            emit ch_wave(wave);
            emit btn_wave(true);
        }
        else {
            emit ch_enemy(enemies);
            win();
        }
    }
    emit ch_enemy(enemies);
    emit ch_money(money);

}

void Game::killEnemy(int prize)
{
    delete sender();
    lootEnemy(prize);

}



