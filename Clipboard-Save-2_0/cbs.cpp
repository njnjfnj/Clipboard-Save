#include "cbs.h"

CBS::CBS(QWidget *parent) : QWidget(parent) {
    settings = new QSettings("ToTUsE", "CBS");
    model = new CBIListModel(QDate::currentDate());
    list = new CBIListView(model);
    isOverOtherApps = false;
    dateLine = new QDateEdit(QDate::currentDate());

    settings->beginGroup("/Settings");
    isNotify = settings->value("/Notify", false).toBool();
    settings->endGroup();

    path = APPDIR + "/data/" +
           QString::number(QDate::currentDate().year())  + '/' +
           QString::number(QDate::currentDate().month()) + '/' +
           QString::number(QDate::currentDate().day());
    d.mkpath(path);

    connect(qApp->clipboard(), &QClipboard::dataChanged, this, &CBS::slotDataChanged);
    connect(dateLine, &QDateEdit::dateChanged, model, &CBIListModel::slotDateChanged);

    showHide = new QAction("Show/Hide Window", this);
    onOffNotify = new QAction("On/Off Notify", this);
    quitWindow = new QAction("Close", this);
    setOverOtherApps = new QAction("+/- on top function");

    connect(showHide, &QAction::triggered, this, &CBS::slotShowHideWindow);
    connect(onOffNotify, &QAction::triggered, this, &CBS::slotOnOffNotify);
    connect(quitWindow, &QAction::triggered, qApp, &QApplication::quit);
    connect(setOverOtherApps, &QAction::triggered, this, &CBS::slotOverOtherApps);

    trayMenu = new QMenu(this);
    trayMenu->addAction(showHide);
    trayMenu->addAction(onOffNotify);
    trayMenu->addAction(setOverOtherApps);
    trayMenu->addSeparator();
    trayMenu->addAction(quitWindow);

    QIcon icon(APPDIR + "/ico.png");

    tray = new QSystemTrayIcon(this);
    tray->setIcon(icon);
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
    connect(m, &QMenu::triggered, this, &CBS::slotMenuTriggered);

    vbl = new QVBoxLayout;
    vbl->addWidget(list);
    vbl->addWidget(dateLine);
    setLayout(vbl);

    settings->beginGroup("/Settings");
    setGeometry(settings->value("/X", -1).toInt(), settings->value("/Y", -1).toInt(), 300, 370);
    settings->endGroup();

    setWindowIcon(icon);
    setWindowTitle("Clipboard-Save");
    setToolTip("double click = hide window");
    list->setToolTip("Double click or ENTER = copy item");

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, 1);
}

CBS::~CBS() {
    settings->beginGroup("/Settings");
        settings->setValue("/X", x());
        settings->setValue("/Y", y());
    settings->endGroup();
    settings->sync();
}

void CBS::NextBackDay(bool state) {
    QDate temp = dateLine->date();
    if(state) {
        temp = temp.addDays(1);
        dateLine->setDate(temp);
    } else {
        temp = temp.addDays(-1);
        dateLine->setDate(temp);
    }
    list->setCurrentIndex(model->index(0));
}

void CBS::setCurrentDate() {
    dateLine->setDate(QDate::currentDate());
    list->setCurrentIndex(model->index(0));
}
