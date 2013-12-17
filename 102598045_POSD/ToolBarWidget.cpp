#include "ToolBarWidget.h"
#include "AddDrawableToolBar.h"
#include "QActionMap.h"

ToolBarWidget::ToolBarWidget(QToolBar* toolBar,QActionMap* actionMap,unsigned int actionIndex) : QToolButton(toolBar){
    QAction* action = actionMap->getQAction(actionIndex);
    this->setDefaultAction(action);
    this->setCheckable(true);
}

ToolBarWidget::~ToolBarWidget(){
}