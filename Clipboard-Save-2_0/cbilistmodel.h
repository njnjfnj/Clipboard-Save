#ifndef CBILISTMODEL_H
#define CBILISTMODEL_H

#include "cbi.h"
#define DATE_FORMAT "hh-mm-ss-zzz"

class CBIListModel : public QAbstractListModel {
Q_OBJECT
public:
    CBIListModel        (const QDate& copyDate, QObject* obj = nullptr);

    QVariant data       (const QModelIndex& index, int role) const;
    bool setData        (const QModelIndex& index, const QVariant& data, int role);

    int rowCount        (const QModelIndex& index = QModelIndex()) const;

    QVariant headerData (int section, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;

    bool insertRows     (int row, int count, const QModelIndex& index = QModelIndex());
    bool removeRows     (int row, int count, const QModelIndex& index = QModelIndex());

    void update();
    void deleteCBI      (const int& indexRow);

    bool addCBI         (const CBI& item);

    CBI getCBI          (const QModelIndex& index);

public slots:
    void slotDateChanged(const QDate& newDate);
private:
    QStringList mList; // main list
    QList<CBI>  CBIList;
    QString     path;
};

#endif // CBILISTMODEL_H
