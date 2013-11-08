#include "ToolBarWidget.h"
#include "ActionData.h"
#include <iostream>

ToolBarWidget::ToolBarWidget(QActionMap* actionMap,string actionName,QWidget* parent) : QToolButton(parent){
    QAction* action = actionMap->getQAction(actionName);
    this->addAction(action);
    this->setIcon(action->icon());
    this->setCheckable(true);
}

ToolBarWidget::~ToolBarWidget(){
}

void ToolBarWidget::mousePressEvent(QMouseEvent* mouseEvent){
}