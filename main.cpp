#include <QApplication>
#include "content.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu menu;
    menu.show();
    return a.exec();
}
