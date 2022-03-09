#ifndef CBS_H
#define CBS_H

#include "cbilistview.h"

class CBS : public QWidget {
    Q_OBJECT
private:
    QDateEdit* dateLine;
    CBIListModel* model;
    CBIListView* list;
    QDir d;
    QString path;
    QSystemTrayIcon* tray;
    QMenu* trayMenu;
    bool isNotify;
    QAction* quitWindow;

protected:
    virtual void closeEvent(QCloseEvent*);
public:
    explicit CBS(QWidget *parent = nullptr);
public slots:
    void slotDataChanged();
    void slotShowHideWindow();
    void slotOnOffNotify();
};

#endif // CBS_H
