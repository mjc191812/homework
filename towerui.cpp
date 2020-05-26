#include "towerui.h"
#include<QPalette>

TowerUI::TowerUI(QWidget *parent) : QWidget(parent)
{
    setFixedSize(220,145);

    power = new QLabel("攻击: ", this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
     power->setPalette(pa);
    radius = new QLabel("半径: ", this);
     radius->setPalette(pa);
    level = new QLabel("等级: ", this);
     level->setPalette(pa);
    sell = new QPushButton("卖出", this);
     sell->setPalette(pa);
    sell->setEnabled(false);
    upgrade = new QPushButton(this);
    upgrade->setEnabled(false);
    levelTower = 999;
    QVBoxLayout * v_box = new QVBoxLayout();
    QHBoxLayout * h_box = new QHBoxLayout();
    h_box->addWidget(upgrade);
    h_box->addWidget(sell);
    v_box->addWidget(level);
    v_box->addWidget(power);
    v_box->addWidget(radius);
    v_box->addLayout(h_box);
    v_box->setAlignment(Qt::AlignBottom);
    setLayout(v_box);
    setUi();
    connect(upgrade, SIGNAL(clicked()), parent, SLOT(upgradeTower()));
    connect(sell, SIGNAL(clicked()), parent, SLOT(cellTower()));
}

void TowerUI::setUi(Tower * tower)
{
    if(tower != nullptr)
    {
        levelTower = tower->getLevel();
        costUp = tower->getCost(levelTower);
        pow = tower->getPower(levelTower);
        rad = tower->getRadius(levelTower);

        if(tower->getLevel() < 2)
        {
            nextCost = tower->getCost(levelTower+1);
            nextPow = tower->getPower(levelTower+1);
            nextRad = tower->getRadius(levelTower+1);

            level->setText(QString("等级: %1 (%2)").arg(levelTower+1).arg(levelTower+2));
            power->setText(QString("攻击: %1 (%2)").arg(pow).arg(nextPow));
            radius->setText(QString("半径: %1 (%2)").arg(rad).arg(nextRad));
            sell->setText(QString("卖出 %1 (%2)").arg(costUp/2).arg(nextCost/2));

            upgrade->setText(QString("升级 %1").arg(costUp));
            checkUp();
        }
        else
        {
            level->setText(QString("等级: %1").arg(levelTower+1));
            power->setText(QString("攻击: %1").arg(pow));
            radius->setText(QString("半径: %1").arg(rad));
            sell->setText(QString("卖出 %1").arg(costUp/2));

            upgrade->setEnabled(false);
            upgrade->setText("最高等级");
        }

        sell->setEnabled(true);
        connect(tower, SIGNAL(up(Tower*)), this, SLOT(setUi(Tower*)));
    }
    else
    {
        levelTower = 999;
        upgrade->setText("升级");
        upgrade->setEnabled(false);

        sell->setText("卖出");
        sell->setEnabled(false);

        power->setText("攻击: ");
        radius->setText("半径: ");
        level->setText("等级: ");

    }
}

void TowerUI::checkUp()
{   
    if(money >= costUp && levelTower < 2)
    {
        upgrade->setEnabled(true);
    }
    else
    {
        upgrade->setEnabled(false);
    }

}

void TowerUI::setMoney(int _money)
{
    money = _money;
    checkUp();
}

