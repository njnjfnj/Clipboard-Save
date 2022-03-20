#ifndef CBS_H
#define CBS_H

#include "cbilistview.h"

class CBS : public QWidget {
    Q_OBJECT
private:
    QDateEdit*          dateLine;
    CBIListModel*       model;
    CBIListView*        list;
    QDir                d;
    QString             path;
    QSystemTrayIcon*    tray;
    QMenu*              trayMenu;
    QMenu*              m;
    bool                isNotify;
    QAction*            quitWindow;

    struct chekMouse {
        int posx;
        int posy;
        bool chek = false;
    };

    chekMouse ch;

protected:
    virtual void closeEvent             (QCloseEvent*) override;
    virtual void mousePressEvent        (QMouseEvent*) override;
    virtual void mouseMoveEvent         (QMouseEvent*) override;
    virtual void paintEvent             (QPaintEvent*) override;
    virtual void contextMenuEvent       (QContextMenuEvent *event) override;
    virtual void mouseDoubleClickEvent  (QMouseEvent *event) override;
public:
    explicit CBS (QWidget *parent = nullptr);
public slots:
    void slotDataChanged    ();
    void slotShowHideWindow ();
    void slotOnOffNotify    ();
    void slotMenuTriggered  (QAction*);
};

#endif // CBS_H
