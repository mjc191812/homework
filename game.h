#pragma once

#include <QtWidgets>
#include <QtMultimedia>
#include "level.h"
#include "builtui.h"
#include "towerui.h"
#include "hud.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget * parent = nullptr);

    void gameOver();
    void win();

signals:
    void stopEnemy();
    void ch_life(int);
    void ch_wave(int);
    void ch_money(int);
    void ch_enemy(int);
    void btn_wave(bool);

public slots:
    void createEnemies();
    void spawnEnemy();
    void wasteLife();
    void reduceMoney(int);
    void cellTower();

    void selectTower(Tower *tower = nullptr);
    void upgradeTower();

private slots:
    void killEnemy(int = 0);
    void lootEnemy(int);

private:
    Tower * selectedTower;
    QMediaPlayer *music;
    LevelParser* parser;
    QTimer * spawnTimer;
    TowerUI * towerUI;
    Level * level;
    HUD* hud;

    builtui build_ui;
    Road road;

    QVector<int> waves;

    int enemies;
    int currentEnemy;
    int wave;
    int life;
    int money;
};


