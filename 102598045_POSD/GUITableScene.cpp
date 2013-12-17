#include "GUITableScene.h"
#include "GraphicalUI.h"
#include "GraphicalPresentation.h"
#include "TableWidget.h"

GUITableScene::GUITableScene(GraphicalUI* graphicalUI) : QGraphicsScene(graphicalUI),graphicalUI(graphicalUI){
    this->graphicalPresentation = this->graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserverToModel(this);
    this->connect(this,SIGNAL(onNotifyEvent()),this,SLOT(executeNotify()));
}

GUITableScene::~GUITableScene(){
    this->graphicalPresentation->unregisterObserverToModel(this);
}

void GUITableScene::notify(Subject* subject){
    this->onNotifyEvent();
}

void GUITableScene::refresh(){
    this->clear();
    //display all
    HashMap<string,Table*> tableMap = this->graphicalPresentation->getAllTables();
    for each(Table* table in tableMap)
        this->addWidget(table);
}

void GUITableScene::addWidget(Table* table){
    TableWidget* tableWidget = new TableWidget(table);
    this->addItem(tableWidget);
    tableWidget->updateWidget();
    this->update();
}

void GUITableScene::executeNotify(){
    this->refresh();
}