#include "cbs.h"
#include "cbi.h"

void CBS::slotDataChanged() {
    d.setPath(path);
    CBI item;

    int count = 0;
    foreach(QChar i, item.Data()){ if(i == ' ') ++count; }
    if(count == item.Data().size()) return void();

    if(model->addCBI(item)){
        QFile f(path + '/' + item.Time().toString(DATE_FORMAT) + ".dat");

        f.open(QIODevice::WriteOnly);
        f.write(item.Data().toStdString().c_str());
        f.close();
    }
    if(isNotify) QApplication::beep();
}

void CBS::slotShowHideWindow(){
    setVisible(!isVisible());
    !isVisible() ? trayMenu->addAction(quitWindow): trayMenu->removeAction(quitWindow);
}
void CBS::slotOnOffNotify() { isNotify = !isNotify; }
