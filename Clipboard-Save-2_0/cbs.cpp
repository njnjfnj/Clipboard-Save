#include "cbs.h"

CBS::CBS(QWidget *parent) : QWidget(parent) {
    model = new CBIListModel(QDate::currentDate());
    isNotify = true;
    list = new CBIListView(model);
    isOverOtherApps = false;



    path = APPDIR + '/' + "data" + '/' +
           QString::number(QDate::currentDate().year()) + '/' +
           QString::number(QDate::currentDate().month()) + '/' +
           QString::number(QDate::currentDate().day());
    d.mkpath(path);

    dateLine = new QDateEdit(QDate::currentDate());

    connect(qApp->clipboard(), SIGNAL(dataChanged()), this, SLOT(slotDataChanged()));
    connect(dateLine, &QDateEdit::dateChanged, model, &CBIListModel::slotDateChanged);

    showHide = new QAction("Show/Hide Window", this);
    connect(showHide, SIGNAL(triggered()), this, SLOT(slotShowHideWindow()));
    onOffNotify = new QAction("On/Off Notify", this);
    connect(onOffNotify, SIGNAL(triggered()), this, SLOT(slotOnOffNotify()));
    quitWindow = new QAction("Close", this);
    connect(quitWindow, SIGNAL(triggered()), qApp, SLOT(quit()));
    setOverOtherApps = new QAction("+/- on top function");
    connect(setOverOtherApps, SIGNAL(triggered()), this, SLOT(slotOverOtherApps()));

    trayMenu = new QMenu(this);
    trayMenu->addAction(showHide);
    trayMenu->addAction(onOffNotify);
    trayMenu->addAction(setOverOtherApps);
    trayMenu->addSeparator();
    trayMenu->addAction(quitWindow);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QPixmap(APPDIR + "/ico.png"));
    tray->setContextMenu(trayMenu);
    tray->setToolTip("Clipboard-Save Tray");
    tray->show();

    m = new QMenu(this);
    m->addAction(onOffNotify);
    m->addAction(setOverOtherApps);
    m->addSeparator();
    m->addAction("hide window");
    m->addSeparator();
    m->addSeparator();
    m->addAction(quitWindow);
    connect(m, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuTriggered(QAction*)));

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(list);
    vbl->addWidget(dateLine);
    setLayout(vbl);

    setWindowIcon(QIcon(APPDIR + "/ico.png"));
    setGeometry(-1, 30, 300, 370);
    setWindowTitle("Clipboard-Save");
    setToolTip("double click = hide window");
    list->setToolTip("Double click or ENTER = copy item");

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, 1);
}

CBS::~CBS() {
    delete dateLine;
    delete model;
    delete list;
    delete tray;
    delete trayMenu;
    delete m;
    delete vbl;
    delete showHide;
    delete onOffNotify;
    delete quitWindow;
    delete setOverOtherApps;
}
