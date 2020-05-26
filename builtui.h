#pragma once
#include <QWidget>
#include "uiobject.h"

class builtui : public QWidget
{
    Q_OBJECT

public:
    builtui(QWidget *parent = nullptr);

private:
    QVBoxLayout v;//垂直布局
    QWidgetList list;//

public slots:
    void sendBuild();
    void setPossible(int money);

signals:
    void build();
};
