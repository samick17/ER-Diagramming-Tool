#include "EditableTableWidgetItem.h"
#include "GraphicalPresentation.h"

EditableTableWidgetItem::EditableTableWidgetItem(GraphicalPresentation* graphicalPresentation,ComponentData* componentData,string text) : graphicalPresentation(graphicalPresentation),componentData(componentData),QLineEdit(text.c_str()){
    connect(this,SIGNAL(editingFinished()),this,SLOT(onEditingFinished()));
    this->setFrame(false);
}

EditableTableWidgetItem::~EditableTableWidgetItem(){
}

ComponentData* EditableTableWidgetItem::getComponentData() const{
    return this->componentData;
}

void EditableTableWidgetItem::onEditingFinished(){
    string text = this->text().toStdString();
    this->graphicalPresentation->setComponentText(componentData->getID(),text);
    this->graphicalPresentation->notify();
}