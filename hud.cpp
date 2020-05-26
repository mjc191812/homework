#include "hud.h"

HUD::HUD(QWidget *parent) : QWidget(parent)
{
    startWave = new QPushButton("下一波");
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    l_wave = new QLabel(this);
     l_wave->setPalette(pa);
    l_life = new QLabel(this);
     l_life->setPalette(pa);
    l_money = new QLabel(this);
     l_money->setPalette(pa);
    l_enemy = new QLabel(this);
     l_enemy->setPalette(pa);

    v_box = new QVBoxLayout(this);
    setLayout(v_box);

    v_box->addWidget (startWave);
    v_box->addWidget(l_wave);
    v_box->addWidget(l_life);
    v_box->addWidget(l_money);
    v_box->addWidget(l_enemy);
    v_box->setAlignment(Qt::AlignTop);

    connect(parent, SIGNAL(ch_life(int)), this, SLOT(life(int)));
    connect(parent, SIGNAL(ch_money(int)), this, SLOT(money(int)));
    connect(parent, SIGNAL(ch_enemy(int)), this, SLOT(enemy(int)));
    connect(parent, SIGNAL(ch_wave(int)), this, SLOT(wave(int)));

    connect(startWave, SIGNAL(clicked()), parent, SLOT(createEnemies()));
    connect(parent, SIGNAL(btn_wave(bool)), startWave, SLOT(setEnabled(bool)));
}

HUD::~HUD()
{
    delete l_enemy;
    delete l_life;
    delete l_money;
    delete l_wave;
    delete startWave;
    delete v_box;
}

void HUD::life(int _life)
{
    l_life->setText(QString("生命值: %1").arg(_life));
}

void HUD::money(int cost)
{
    l_money->setText(QString("金钱: %1").arg(cost));
}

void HUD::enemy(int size)
{
    l_enemy->setText(QString("敌人数目: %1").arg(size));
}

void HUD::wave(int current)
{
    l_wave->setText(QString("波数: %1").arg(current+1));
}
