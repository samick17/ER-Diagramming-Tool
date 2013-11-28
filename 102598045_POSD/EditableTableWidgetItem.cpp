#include "EditableTableWidgetItem.h"

EditableTableWidgetItem::EditableTableWidgetItem(ComponentData* componentData,string text) : componentData(componentData),QTableWidgetItem(text.c_str()){
}

EditableTableWidgetItem::~EditableTableWidgetItem(){
}

ComponentData* EditableTableWidgetItem::getComponentData() const{
    return this->componentData;
}