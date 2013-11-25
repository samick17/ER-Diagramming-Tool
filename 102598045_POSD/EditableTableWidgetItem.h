#pragma once

#include <QTableWidgetItem>
#include "ComponentData.h"

class EditableTableWidgetItem : public QTableWidgetItem{
public:
    EditableTableWidgetItem(ComponentData* componentData,string text);
    ~EditableTableWidgetItem();

    ComponentData* getComponentData() const;
private:
    ComponentData* componentData;
};