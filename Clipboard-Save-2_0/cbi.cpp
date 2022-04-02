#include "cbi.h"

CBI::CBI    (                                   ) {
    data = QApplication::clipboard()->text(),
    t = QTime::currentTime();
}
CBI::CBI    (QString copyData, QTime copyTime   ) {
    data = copyData;
    t = copyTime;
}

QTime CBI::Time() const     { return t;     }
QString CBI::Data() const   { return data;  }

bool operator == (const CBI& first, const CBI& second) {
    return first.Data() == second.Data();
}
