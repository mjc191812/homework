#include "content.h"
#include "game.h"

Menu::Menu(QWidget *parent)
{
    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QImage(":res/images/back.jpg")));
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    setWindowTitle("辉夜大小姐之单身狗的反击大作战");
    setFixedSize(400,600);
//设置开始按钮
    startgame.setText("开始游戏");
    startgame.setParent(this);
    startgame.resize(200,30);
    startgame.move(100,20);
//打开游戏
    connect(&startgame, SIGNAL(clicked()), this, SLOT(begin()));
//设置关闭按钮
    quit.setText("退出");
    quit.setParent(this);
    quit.resize(200,30);
    quit.move(100,60);
//关闭游戏
    connect(&quit, SIGNAL(clicked()), this, SLOT(close()));
    Q_UNUSED(parent);
}

void Menu::begin()//开启新页面
{
    Game * game  = new Game();
    this->close();
    game->show();
}
