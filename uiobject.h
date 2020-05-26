#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <QWidget>

class UiObject : public QWidget
{
    Q_OBJECT
public:
    explicit UiObject(QWidget *parent = nullptr);

signals:

};

#endif // UIOBJECT_H
