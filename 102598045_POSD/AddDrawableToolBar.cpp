#include "AddDrawableToolBar.h"
#include "ToolBarWidget.h"
#include "ActionData.h"

AddDrawableToolBar::AddDrawableToolBar(QActionMap* actionMap,QWidget* parent) : QToolBar(parent){
    this->addWidget(new ToolBarWidget(actionMap,ActionData::PointerState,this));
    this->addWidget(new ToolBarWidget(actionMap,ActionData::ConnectState,this));
    this->addWidget(new ToolBarWidget(actionMap,ActionData::AttributeState,this));
    this->addWidget(new ToolBarWidget(actionMap,ActionData::EntityState,this));
    this->addWidget(new ToolBarWidget(actionMap,ActionData::RelationShipState,this));
}

AddDrawableToolBar::~AddDrawableToolBar(){
}