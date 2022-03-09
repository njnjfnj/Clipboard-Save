#include "cbs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f(QApplication::applicationDirPath() + '/' + "style.css");
    f.open(QIODevice::ReadOnly);
    a.setStyleSheet(f.readAll());

    CBS w;
    w.show();

    return a.exec();
}
