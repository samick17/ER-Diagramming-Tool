#include "AddDrawableToolBar.h"
#include "ToolBarWidget.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "StateID.h"
#include <iostream>

AddDrawableToolBar::AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    this->currentWidget = NULL;
    this->toolBarWidgetMap.put(StateID::PointerState,new ToolBarWidget(this,actionMap,ActionData::PointerState));
    this->toolBarWidgetMap.put(StateID::ConnectState,new ToolBarWidget(this,actionMap,ActionData::ConnectState));
    this->toolBarWidgetMap.put(StateID::AttributeState,new ToolBarWidget(this,actionMap,ActionData::AttributeState));
    this->toolBarWidgetMap.put(StateID::EntityState,new ToolBarWidget(this,actionMap,ActionData::EntityState));
    this->toolBarWidgetMap.put(StateID::RelationShipState,new ToolBarWidget(this,actionMap,ActionData::RelationShipState));
    for each(ToolBarWidget* toolBarWidget in toolBarWidgetMap)
        this->addWidget(toolBarWidget);
}

AddDrawableToolBar::~AddDrawableToolBar(){
}

void AddDrawableToolBar::selectToolButton(int stateID){
    if(this->currentWidget != NULL)
        this->currentWidget->setChecked(false);
    ToolBarWidget* nextSelectToolButton = this->toolBarWidgetMap.get(stateID);
    nextSelectToolButton->setChecked(true);
    this->currentWidget = nextSelectToolButton;
}