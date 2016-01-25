#ifndef SLOTTABLE_H
#define SLOTTABLE_H

#include "qtablewidget.h"
#include "QTableWidgetItem"

class SlotTable : public QObject
{
    Q_OBJECT

public:
    QTableWidget * destination;
    QTableWidget * source;
    SlotTable();
    ~SlotTable();
public slots:
    void UpdateTable(int, int);
    void CheckConflict(int, int);
};

#endif // SLOTTABLE_H
