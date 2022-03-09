#ifndef CBILISTVIEW_H
#define CBILISTVIEW_H

#include "cbilistmodel.h"

class CBIListView : public QListView {
    Q_OBJECT
    QMenu* m;
    CBIListModel* CBIModel;
public:
    CBIListView(CBIListModel* model, QWidget* qw = NULL);

    virtual void contextMenuEvent(QContextMenuEvent* ev) override;
    void keyPressEvent(QKeyEvent* ev) override;
public slots:
    void slotMenuTriggered(QAction* ac);
    void slotItemDoubleClicked(const QModelIndex& index);
};

#endif // CBILISTVIEW_H
