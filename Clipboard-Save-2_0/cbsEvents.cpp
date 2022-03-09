#include "cbs.h"

void CBS::closeEvent(QCloseEvent *ev){
    Q_UNUSED(ev);
    if(tray->isVisible()) hide();
}
