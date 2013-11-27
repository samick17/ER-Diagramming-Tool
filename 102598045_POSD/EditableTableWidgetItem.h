#pragma once

#include <QLineEdit>
#include "ComponentData.h"

class GraphicalPresentation;

class EditableTableWidgetItem : public QLineEdit{
    Q_OBJECT
public:
    EditableTableWidgetItem(GraphicalPresentation* graphicalPresentation,ComponentData* componentData,string text);
    ~EditableTableWidgetItem();

    ComponentData* getComponentData() const;
private:
    GraphicalPresentation* graphicalPresentation;
    ComponentData* componentData;
private slots:
    void onEditingFinished();
};