#include "copywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CopyWidget w;
    w.show();

    return a.exec();
}
