#ifndef CBI_H
#define CBI_H

#include <QtWidgets>

class CBI {
Q_GADGET
    QTime t;
    QString data;
public:
    CBI();
    CBI(QString copyData, QTime copyTime);

    QTime Time() const;
    QString Data() const;

    friend bool operator == (const CBI& first, const CBI& second);
};

#endif // CBI_H
