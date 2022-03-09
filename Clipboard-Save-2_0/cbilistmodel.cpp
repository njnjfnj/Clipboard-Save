#include "cbilistmodel.h"

CBIListModel::CBIListModel(const QDate& copyDate, QObject* obj) : QAbstractListModel(obj){
    path = QApplication::applicationDirPath() + '/' + "data" + '/' +
           QString::number(copyDate.year()) + '/' +
           QString::number(copyDate.month()) + '/' +
           QString::number(copyDate.day());

    update();
}

QVariant CBIListModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || index.row() < 0 || index.row() > mList.size()) return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? mList.at(index.row()) : QVariant();
}

bool CBIListModel::setData(const QModelIndex &index, const QVariant& data, int role) {
    if(index.isValid() && role == Qt::EditRole){
        mList[index.row()] = data.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int CBIListModel::rowCount(const QModelIndex& index) const {
    if(index.isValid()) return 0;
    return mList.size();
}

QVariant CBIListModel::headerData(int section, Qt::Orientation orientation, int nRole) const {
    if(nRole == Qt::DisplayRole) return QVariant();
    return orientation == Qt::Horizontal ? QString("copy data") : QString::number(section);
}

bool CBIListModel::insertRows(int row, int count, const QModelIndex &index) {
    if(index.isValid()) return false;

    beginInsertRows(QModelIndex(), row, count - 1);
    for(qint16 i = 0; i < count ; ++i){
        mList.insert(row, "");
    }
    endInsertRows();

    return true;
}

bool CBIListModel::removeRows(int row, int count, const QModelIndex &index) {
    if(index.isValid()) return false;

    beginRemoveRows(QModelIndex(), row, count - 1);
    for(qint16 i = 0; i < count ; ++i){
        mList.removeAt(i);
    }
    endRemoveRows();

    return true;
}

void CBIListModel::update() {
    QApplication::processEvents();
beginResetModel();
    QDir d(path);
    QStringList pathList = d.entryList(QStringList() << "*.dat", QDir::Files);

    CBIList.clear();
    mList.clear();

    foreach(QString file, pathList) {
        QFile f(d.absoluteFilePath(file));
        f.open(QIODevice::ReadOnly);
        file.resize(file.size() - 4);
        CBIList.push_front(CBI(f.readAll(), QTime::fromString(file, DATE_FORMAT)));
        QString temp = CBIList.front().Data();
        if(temp.size() > 100) temp.resize(100);
        mList.push_front(temp);
    }

endResetModel();
}

void CBIListModel::deleteCBI(const int& indexRow) {
    beginRemoveRows(QModelIndex(), indexRow, 0);

    mList.removeAt(indexRow);
    QFile f(path + '/' + CBIList.at(indexRow).Time().toString(DATE_FORMAT) + ".dat");
    f.remove();
    CBIList.removeAt(indexRow);

    endRemoveRows();
}

bool CBIListModel::addCBI(const CBI &item) {

    foreach(CBI i, CBIList) {
        if(i == item) {
            return false;
        }
    }

    beginInsertRows(QModelIndex(), 0, 1);
    CBIList.push_front(item);
    QString temp = item.Data();
    if(temp.size() > 100) {
        temp.resize(100);
        temp.push_back("...");
    }
    mList.push_front(temp);
    endInsertRows();

    return true;
}

CBI CBIListModel::getCBI(const QModelIndex& index) { return CBIList.at(index.row()); }

// slots
void CBIListModel::slotDateChanged(const QDate &newDate) {
    path = QApplication::applicationDirPath() + '/' + "data" + '/' +
           QString::number(newDate.year()) + '/' +
           QString::number(newDate.month()) + '/' +
           QString::number(newDate.day());
    update();
}
