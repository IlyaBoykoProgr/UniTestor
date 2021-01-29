#include "thewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TheWindow w;
    w.show();
    return a.exec();
}
