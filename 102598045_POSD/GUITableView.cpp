#include "GUITableView.h"
#include <QHeaderView>
#include "GraphicalPresentation.h"
#include "EditableTableWidgetItem.h"
#include "Number.h"

const int GUITableView::TableSize = 2;
const string GUITableView::TableColumnTypeName = "Type";
const string GUITableView::TableColumnTextName = "Text";

GUITableView::GUITableView(GraphicalPresentation* graphicalPresentation) : QTableWidget(),graphicalPresentation(graphicalPresentation){
    this->setColumnCount(TableSize);
    this->setHorizontalHeaderLabels(QStringList() << TableColumnTypeName.c_str() << TableColumnTextName.c_str());
    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    this->graphicalPresentation->registerObserver(this);
    this->connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
}

GUITableView::~GUITableView(){
    this->graphicalPresentation->unregisterObserver(this);
}
//disconnect signal & onItemChanged to avoid loop,finally reconnect them
void GUITableView::notify(Subject* subject){
    disconnect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
    this->clearContents();
    HashMap<string,ComponentData*> componentDataMap = this->graphicalPresentation->getAllComponentDataMap();
    this->setRowCount(componentDataMap.size());
    unsigned int index = 0;
    for each(ComponentData* componentData in componentDataMap){
        QTableWidgetItem* itemType = new QTableWidgetItem(componentData->getClassName().c_str());
        itemType->setFlags(itemType->flags() ^ Qt::ItemIsEditable);
        this->setItem(index,Number::Zero,itemType);
        EditableTableWidgetItem* itemText = new EditableTableWidgetItem(componentData,componentData->getName());
        this->setItem(index,Number::One,itemText);
        index++;
    }
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
}
//itemChanged,call presentation updateComponentText
void GUITableView::onItemChanged(QTableWidgetItem* tableWidgetItem){
    EditableTableWidgetItem* itemText = dynamic_cast<EditableTableWidgetItem*>(tableWidgetItem);
    if(itemText){
        ComponentData* componentData = itemText->getComponentData();
        this->graphicalPresentation->setComponentText(componentData->getID(),tableWidgetItem->text().toStdString());
    }
}