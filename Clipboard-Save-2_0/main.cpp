#include "cbs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f(APPDIR + "/style.css");
    f.open(QIODevice::ReadOnly);
    a.setStyleSheet(f.readAll());
    f.close();

    CBS w;

    return a.exec();
}
