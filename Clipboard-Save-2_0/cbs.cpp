#include "cbs.h"

CBS::CBS(QWidget *parent) : QWidget(parent) {
    model = new CBIListModel(QDate::currentDate());
    dateLine = new QDateEdit(QDate::currentDate());
    list = new CBIListView(model);
    isNotify = true;

    path = QApplication::applicationDirPath() + '/' + "data" + '/' +
           QString::number(QDate::currentDate().year()) + '/' +
           QString::number(QDate::currentDate().month()) + '/' +
           QString::number(QDate::currentDate().day());
    d.mkpath(path);

    connect(qApp->clipboard(), &QClipboard::dataChanged, this, &CBS::slotDataChanged);
    connect(dateLine, &QDateEdit::dateChanged, model, &CBIListModel::slotDateChanged);

    QAction* showHide = new QAction("Show/Hide Window", this);
    connect(showHide, &QAction::triggered, this, &CBS::slotShowHideWindow);
    QAction* onOffNotify = new QAction("On/Off Notify", this);
    connect(onOffNotify, &QAction::triggered, this, &CBS::slotOnOffNotify);
    quitWindow = new QAction("Quit", this);
    connect(quitWindow, &QAction::triggered, qApp, &QApplication::quit);

    trayMenu = new QMenu(this);
    trayMenu->addAction(showHide);
    trayMenu->addAction(onOffNotify);
    trayMenu->addSeparator();

    tray = new QSystemTrayIcon(QIcon(QPixmap(QApplication::applicationDirPath() + '/' + "ico.png")), this);
    tray->setContextMenu(trayMenu);
    tray->setToolTip("Clipboard-Save Tray");
    tray->show();

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(list);
    vbl->addWidget(dateLine);
    setLayout(vbl);

    setWindowIcon(QPixmap(QApplication::applicationDirPath() + '/' + "ico.png"));
    setGeometry(-1, 30, 300, 600);
}


