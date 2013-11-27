#include "GUITableView.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "GraphicalPresentation.h"
#include "EditableTableWidgetItem.h"

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
        QWidget* itemText = new EditableTableWidgetItem(this->graphicalPresentation,componentData,componentData->getName());
        this->setCellWidget(index,1,itemText);
        index++;
    }
}