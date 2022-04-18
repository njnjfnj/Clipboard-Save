#include "cbs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f(APPDIR + "/style.css");
    f.open(QIODevice::ReadOnly);

    CBS w;

    w.setStyleSheet(f.readAll());
    f.close();

    return a.exec();
}
