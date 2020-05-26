#include "builtui.h"
#include<QPalette>
builtui::builtui(QWidget *parent) : QWidget(parent)
{
    v.setAlignment(Qt::AlignTop);//消除布局中的空隙，让控件紧紧挨在一起

    QLabel * name = new QLabel("<b>防御塔:<b>");
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    name->setPalette((pa));
    UiObject * obj = new UiObject();
    QLabel * cost = new QLabel(QString("花费: %1").arg(obj->getCost()));
    cost->setPalette(pa);
    QLabel * radius = new QLabel("半径: 200");
    radius->setPalette(pa);
    QLabel * power = new QLabel( QString("攻击: 30"));
    power->setPalette(pa);
    v.addWidget(name);
//通过list存要放上去的标签
    list.push_back(obj);
    list.push_back(cost);
    list.push_back(radius);
    list.push_back(power);
    connect(obj, SIGNAL(create()), this, SLOT(sendBuild()));
//其实用迭代器也行 但是还是auto方便一点
    for(auto x : list)
    {
        v.addWidget(x);
    }
    this->setLayout(&v);
    this->setContentsMargins(2,2,2,2);//设置边距

}

void builtui::sendBuild()
{
    emit build();//触发建造
}

void builtui::setPossible(int money)//检查钱够不够
{
    for(auto i : list)
    {
        if (UiObject * obj = dynamic_cast<UiObject*>(i))
        {
            if(money < obj->getCost())
            {
                i->setEnabled(false);//不够return fasle
            }
            else
            {
                i->setEnabled(true);//够了return true
            }
        }
    }
}


