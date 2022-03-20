#ifndef CBILISTVIEW_H
#define CBILISTVIEW_H

#include "cbilistmodel.h"

class CBIListView : public QListView {
    Q_OBJECT
    QMenu*          m;
    CBIListModel*   CBIModel;
    QMessageBox* msg;
public:
    CBIListView                     (CBIListModel* model, QWidget* qw = NULL);
protected:
    virtual void contextMenuEvent       (QContextMenuEvent*) override;
    virtual void keyPressEvent          (QKeyEvent*) override;
    virtual void mouseDoubleClickEvent  (QMouseEvent*) override;
public slots:
    void slotMenuTriggered          (QAction*);
    void slotItemDoubleClicked      (const QModelIndex&);
};

#endif // CBILISTVIEW_H
