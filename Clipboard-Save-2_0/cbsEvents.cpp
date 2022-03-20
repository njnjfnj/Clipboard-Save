#include "cbs.h"

void CBS::closeEvent(QCloseEvent *ev){
    Q_UNUSED(ev);
    if(tray->isVisible()) hide();
}

void CBS::paintEvent(QPaintEvent *ev) {
    Q_UNUSED(ev)
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(QRect(0, 0, width(), height()), 5, 5);
    p.fillPath(path, QColor(0, 0, 0, 67));
}

void CBS::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) ch.posx = ev->x(), ch.posy = ev->y(), ch.chek = 1;
    else ch.chek = 0;
}

void CBS::mouseMoveEvent(QMouseEvent *ev) {
    if(ch.chek && ev->buttons() == Qt::LeftButton) setGeometry(ev->globalX() - ch.posx, ev->globalY() - ch.posy, width(), height());
}

void CBS::contextMenuEvent(QContextMenuEvent *ev) {
    m->exec(ev->globalPos());
}

void CBS::mouseDoubleClickEvent(QMouseEvent *ev) {
    Q_UNUSED(ev)
    hide();
}
