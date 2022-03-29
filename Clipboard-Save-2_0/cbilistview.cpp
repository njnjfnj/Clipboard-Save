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
            QDialog dio(NULL, Qt::WindowCloseButtonHint);

            QTextEdit txt;
            QLabel lbl(CBIModel->getCBI(currentIndex()).Time().toString("hh:mm"));

            txt.setReadOnly(true);
            txt.setText(CBIModel->getCBI(currentIndex()).Data());

            QVBoxLayout vbl;
            vbl.addWidget(&txt);
            vbl.addWidget(&lbl);
            dio.setLayout(&vbl);
            dio.exec();
            dio.done(0);
        } else if (i == "Copy") {
            qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
        } else if (i == "Delete") {
            CBIModel->deleteCBI(currentIndex().row());
        }
    }
}


// Events
void CBIListView::keyPressEvent(QKeyEvent *ev) {
    if(ev->key() == Qt::Key_Delete && currentIndex().isValid()){
        CBIModel->deleteCBI(currentIndex().row());
    } else if( ev->key() == Qt::Key_Return &&  currentIndex().isValid())  {
        qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
    } else if(ev->key() == Qt::Key_Up && currentIndex().isValid() && currentIndex().row() != 0) {
        setCurrentIndex(CBIModel->index(currentIndex().row() - 1, 0));
    } else if(ev->key() == Qt::Key_Down && currentIndex().isValid() && currentIndex().row() < CBIModel->Size()){
        setCurrentIndex(CBIModel->index(currentIndex().row() + 1, 0));
    } else if(ev->key() == Qt::Key_Up && !currentIndex().isValid() && !CBIModel->isEmpty()) {
        setCurrentIndex(CBIModel->index(CBIModel->Size() - 1, 0));
    } else if(ev->key() == Qt::Key_Escape) {
        parentWidget()->hide();
    } else if(ev->key() == Qt::Key_Escape){
        static_cast<CBS>(parentWidget()).hide();
    }
}

void CBIListView::contextMenuEvent(QContextMenuEvent* ev) {
    m->exec(ev->globalPos());
}

void CBIListView::mouseDoubleClickEvent(QMouseEvent *ev) {
    Q_UNUSED(ev)
    if(currentIndex().isValid()) qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
}
