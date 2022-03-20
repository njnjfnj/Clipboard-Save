#include "cbilistview.h"

CBIListView::CBIListView(CBIListModel* model, QWidget* qw) : QListView(qw) {
    m = new QMenu(this);
    msg = new QMessageBox;
    CBIModel = model;
    setModel(CBIModel);

    m->addAction("Info...");
    m->addAction("Copy");
    m->addSeparator();
    m->addAction("Delete");

    connect(m, &QMenu::triggered, this, &CBIListView::slotMenuTriggered);
    connect(this, &CBIListView::doubleClicked, this, &CBIListView::slotItemDoubleClicked);
}


// Slots
void CBIListView::slotItemDoubleClicked(const QModelIndex& index) {
    qApp->clipboard()->setText(CBIModel->getCBI(index).Data());
}

void CBIListView::slotMenuTriggered(QAction* ac) {
    QString i = ac->text(); // info of clicked action
    if(i == "Info..."){
        QDialog dio(NULL, Qt::WindowCloseButtonHint);

        QTextEdit* txt = new QTextEdit;
        QLabel* lbl = new QLabel(CBIModel->getCBI(currentIndex()).Time().toString("hh:mm"));

        txt->setReadOnly(true);
        txt->setText(CBIModel->getCBI(currentIndex()).Data());

        QVBoxLayout* vbl = new QVBoxLayout;
        vbl->addWidget(txt);
        vbl->addWidget(lbl);
        dio.setLayout(vbl);
        dio.exec();

        delete txt;
        delete lbl;
        delete vbl;
    } else if (i == "Copy") {
        qApp->clipboard()->setText(CBIModel->getCBI(currentIndex()).Data());
    } else if (i == "Delete" && msg->warning
               (0, "Warning", "The text will be deleted permanently!\nDo you want to delete?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No
                ) == QMessageBox::Yes) {
        CBIModel->deleteCBI(currentIndex().row());
        msg->close();
    }
}


// Events
void CBIListView::keyPressEvent(QKeyEvent *ev) {
    if(ev->key() == Qt::Key_Delete && currentIndex().isValid() && QMessageBox::warning
            (0, "Warning", "The text will be deleted permanently!\nDo you want to delete?",
             QMessageBox::Yes | QMessageBox::No,
             QMessageBox::No
             ) == QMessageBox::Yes){
        CBIModel->deleteCBI(currentIndex().row());
    }
}

void CBIListView::contextMenuEvent(QContextMenuEvent* ev) {
    m->exec(ev->globalPos());
}

void CBIListView::mouseDoubleClickEvent(QMouseEvent *ev) {
    parentWidget()->hide();
}
