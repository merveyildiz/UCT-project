#include "slottable.h"

SlotTable::SlotTable()
{

}

SlotTable::~SlotTable()
{

}

void SlotTable::UpdateTable(int row, int column){
    QTableWidgetItem * dest_cell;
    dest_cell = destination->item(row, column);
    if(dest_cell){
        destination->item(row, column)->setText(source->item(row, column)->text());
    }else{
        destination->setItem(row, column, new QTableWidgetItem(source->item(row, column)->text()));
    }
}

void SlotTable::CheckConflict(int row, int column){

}
