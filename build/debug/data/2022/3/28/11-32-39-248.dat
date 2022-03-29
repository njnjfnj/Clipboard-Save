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

void CBS::slotShowHideWindow(){ setVisible(!isVisible()); }
void CBS::slotOnOffNotify() { isNotify = !isNotify; }

void CBS::slotMenuTriggered(QAction* a) {
    if(a->text() == "hide window") hide();
}

void CBS::slotOverOtherApps() {
    isOverOtherApps = !isOverOtherApps;
    setWindowFlag(Qt::WindowStaysOnTopHint, isOverOtherApps);
    show();
}
