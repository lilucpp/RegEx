#include "regex.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegEx w;
    w.show();

    return a.exec();
}
