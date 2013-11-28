#include "ToolBarWidget.h"
#include "AddDrawableToolBar.h"
#include "QActionMap.h"

ToolBarWidget::ToolBarWidget(AddDrawableToolBar* toolBar,QActionMap* actionMap,unsigned int actionIndex) : toolBar(toolBar),QToolButton(toolBar){
    QAction* action = actionMap->getQAction(actionIndex);
    this->setDefaultAction(action);
    this->setCheckable(true);
}

ToolBarWidget::~ToolBarWidget(){
}