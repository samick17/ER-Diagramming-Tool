#include "GUITableView.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "GraphicalPresentation.h"
#include "EditableTableWidgetItem.h"
#include <iostream>

const int GUITableView::TableSize = 2;
const string GUITableView::TableColumnTypeName = "Type";
const string GUITableView::TableColumnTextName = "Text";

GUITableView::GUITableView(GraphicalPresentation* graphicalPresentation) : QTableWidget(),graphicalPresentation(graphicalPresentation){
    this->setColumnCount(TableSize);
    this->setHorizontalHeaderLabels(QStringList() << TableColumnTypeName.c_str() << TableColumnTextName.c_str());
    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    this->graphicalPresentation->registerObserver(this);
}

GUITableView::~GUITableView(){
    this->graphicalPresentation->unregisterObserver(this);
}

void GUITableView::notify(ISubject* subject){
    this->clearContents();
    HashMap<string,ComponentData*> componentDataMap = this->graphicalPresentation->getAllComponentDataMap();
    this->setRowCount(componentDataMap.size());
    unsigned int index = 0;
    for each(ComponentData* componentData in componentDataMap){
        QTableWidgetItem* itemType = new QTableWidgetItem(componentData->getType().c_str());
        itemType->setFlags(itemType->flags() ^ Qt::ItemIsEditable);
        this->setItem(index,0,itemType);
        QTableWidgetItem* itemText = new EditableTableWidgetItem(componentData,componentData->getName());
        this->setItem(index,1,itemText);
        index++;
    }
}

void GUITableView::keyReleaseEvent(QKeyEvent* keyEvent){
    if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
        EditableTableWidgetItem* tableWidgetItem = dynamic_cast<EditableTableWidgetItem*>(this->currentItem());
        if(!tableWidgetItem)
            return;
        ComponentData* componentData = tableWidgetItem->getComponentData();
        string text = tableWidgetItem->text().toStdString();
        this->graphicalPresentation->setComponentText(componentData->getID(),text);
        this->graphicalPresentation->notify();
    }
}