#include "cbs.h"

CBIListView::CBIListView(CBIListModel* model, QWidget* qw) : QListView(qw) {
    m = new QMenu(this);
    CBIModel = model;
    setModel(CBIModel);

    m->addAction("Info...");
    m->addAction("Copy");
    m->addSeparator();
    m->addAction("Delete");

    connect(m, &QMenu::triggered, this, &CBIListView::slotMenuTriggered);
    connect(this, &CBIListView::doubleClicked, this, &CBIListView::slotItemDoubleClicked);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

CBIListView::~CBIListView() {
    delete m;
}


// Slots
void CBIListView::slotItemDoubleClicked(const QModelIndex& index) {
    qApp->clipboard()->setText(CBIModel->getCBI(index).Data());
}

void CBIListView::slotMenuTriggered(QAction* ac) {
    QString i = ac->text(); // info of clicked action
    if(currentIndex().isValid()){
        if(i == "Info..."){
            QDialog *dio = new QDialog(NULL, Qt::WindowCloseButtonHint);
            CBI tempCBI = CBIModel->getCBI(currentIndex());
            QTextEdit* txt = new QTextEdit;
            QLabel *lbl = new QLabel(tempCBI.Time().toString("hh:mm"));

            txt->setReadOnly(true);
            txt->setText(tempCBI.Data());

            QVBoxLayout *vbl = new QVBoxLayout;
            vbl->addWidget(txt);
            vbl->addWidget(lbl);
            dio->setLayout(vbl);
            dio->exec();

            delete txt;
            delete lbl;
            delete vbl;
            delete dio;
        } else if (i == "Copy") {
            qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
        } else if (i == "Delete") {
            CBIModel->deleteCBI(currentIndex().row());
        }
    }
}


// Events
void CBIListView::keyPressEvent(QKeyEvent *ev) {
    int key = ev->key();
           if(key == Qt::Key_Delete && currentIndex().isValid()                                            ){ CBIModel->deleteCBI(currentIndex().row());
    } else if(key == Qt::Key_Return && currentIndex().isValid()                                            ){ qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
    } else if(key == Qt::Key_Up     && currentIndex().isValid() &&  currentIndex().row() != 0              ){ setCurrentIndex(CBIModel->index(currentIndex().row() - 1, 0));
    } else if(key == Qt::Key_Down   && currentIndex().isValid() &&  currentIndex().row() < CBIModel->Size()){ setCurrentIndex(CBIModel->index(currentIndex().row() + 1, 0));
    } else if(key == Qt::Key_Up     && !currentIndex().isValid() && !CBIModel->isEmpty()                   ){ setCurrentIndex(CBIModel->index(CBIModel->Size() - 1, 0));
    } else if(key == Qt::Key_Escape                                                                        ){ parentWidget()->hide();
    } else if(key == Qt::Key_Right                                                                         ){ static_cast<CBS*>(parentWidget())->NextBackDay(1);
    } else if(key == Qt::Key_Left                                                                          ){ static_cast<CBS*>(parentWidget())->NextBackDay(0);
    } else if(key == Qt::Key_C || key == 1057                                                              ){ static_cast<CBS*>(parentWidget())->setCurrentDate();
    }
}

void CBIListView::contextMenuEvent(QContextMenuEvent* ev) { m->exec(ev->globalPos()); }

void CBIListView::mouseDoubleClickEvent(QMouseEvent *ev) {
    Q_UNUSED(ev)
    if(currentIndex().isValid()) qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
}
