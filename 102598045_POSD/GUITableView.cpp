#include "GUITableView.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include "GraphicalPresentation.h"

const string GUITableView::TableTitle = "Components";
const int GUITableView::TableSize = 2;
const string GUITableView::TableColumnTypeName = "Type";
const string GUITableView::TableColumnTextName = "Text";

GUITableView::GUITableView(GraphicalPresentation* graphicalPresentation) : QWidget(),graphicalPresentation(graphicalPresentation){
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    this->titleLabel = new QLabel(TableTitle.c_str());
    this->titleLabel->setAlignment(Qt::AlignCenter);
    this->tableWidget = new QTableWidget();
    this->tableWidget->setColumnCount(TableSize);
    this->tableWidget->setHorizontalHeaderLabels(QStringList() << TableColumnTypeName.c_str() << TableColumnTextName.c_str());
    this->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    layout->addWidget(this->titleLabel);
    layout->addWidget(this->tableWidget);
    this->graphicalPresentation->registerObserver(this);
}

GUITableView::~GUITableView(){
    this->graphicalPresentation->unregisterObserver(this);
}

void GUITableView::notify(ISubject* subject){
    this->tableWidget->clearContents();

    HashMap<string,ComponentData*> componentDataMap = this->graphicalPresentation->getAllComponentDataMap();
    this->tableWidget->setRowCount(componentDataMap.size());
    unsigned int index = 0;
    for each(ComponentData* componentData in componentDataMap){
        this->tableWidget->setItem(index,0,new QTableWidgetItem(componentData->getType().c_str()));
        this->tableWidget->setItem(index,1,new QTableWidgetItem(componentData->getName().c_str()));
        index++;
    }
}