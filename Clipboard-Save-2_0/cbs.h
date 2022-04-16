#ifndef CBS_H
#define CBS_H

#include "cbilistmodel.h"

class CBIListView;

class CBS : public QWidget {
    Q_OBJECT
private:
    QSettings*          settings;
    QVBoxLayout*        vbl;
    QDateEdit*          dateLine;
    CBIListModel*       model;
    CBIListView*        list;
    QDir                d;
    QString             path;
    QSystemTrayIcon*    tray;
    QMenu*              trayMenu;
    QMenu*              m;

    bool                isNotify;
    bool                isOverOtherApps;

    QAction*            showHide;
    QAction*            onOffNotify;
    QAction*            quitWindow;
    QAction*            setOverOtherApps;

    struct chekMouse {
        int posx;
        int posy;
        bool chek = false;
    };

    chekMouse ch;

protected:
    virtual void closeEvent             (QCloseEvent*               ) override;
    virtual void mousePressEvent        (QMouseEvent*               ) override;
    virtual void mouseMoveEvent         (QMouseEvent*               ) override;
    virtual void paintEvent             (QPaintEvent*               ) override;
    virtual void contextMenuEvent       (QContextMenuEvent *event   ) override;
public:
    explicit CBS (QWidget *parent = nullptr);
    ~CBS();
    void NextBackDay    (bool);
    void setCurrentDate (    );
public slots:
    void slotDataChanged    (       );
    void slotShowHideWindow (       );
    void slotOnOffNotify    (       );
    void slotOverOtherApps  (       );
    void slotMenuTriggered  (QAction*);
};

class CBIListView : public QListView {
    Q_OBJECT
    QMenu* m;
    CBIListModel*   CBIModel;
public:
    explicit CBIListView    (CBIListModel* model, QWidget* qw = NULL);
    ~CBIListView();
protected:
    virtual void contextMenuEvent       (QContextMenuEvent*) override;
    virtual void keyPressEvent          (QKeyEvent*) override;
    virtual void mouseDoubleClickEvent  (QMouseEvent*) override;
public slots:
    void slotMenuTriggered          (QAction*);
    void slotItemDoubleClicked      (const QModelIndex&);
};

#endif // CBS_H
