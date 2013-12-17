#include "BrowseToolBar.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "ToolBarWidget.h"
#include "GraphicalPresentation.h"

BrowseToolBar::BrowseToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    this->browseDBTableWidget = new ToolBarWidget(this,actionMap,ActionData::BrowseDB);
    this->addWidget(this->browseDBTableWidget);
    this->graphicalPresentation = graphicalUI->getGraphicalPresentation();
}

BrowseToolBar::~BrowseToolBar(){
}

void BrowseToolBar::notify(Subject* subject){
    this->browseDBTableWidget->setChecked(this->graphicalPresentation->getIsDisplayDBTable());
}