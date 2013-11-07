#include "AddDrawableToolBar.h"
#include "ActionData.h"
#include <QList>
#include <QToolButton>
#include "SetPointerWidget.h"

AddDrawableToolBar::AddDrawableToolBar(QActionMap* actionMap,QWidget* parent) : QToolBar(parent){
	this->addWidget(new SetPointerWidget(actionMap,this));
    //QAction* setPointerStateAction = actionMap->getQAction(ActionData::PointerState);
    QAction* setConnectStateAction = actionMap->getQAction(ActionData::ConnectState);
    QAction* setAttributeStateAction = actionMap->getQAction(ActionData::AttributeState);
    QAction* setEntityStateAction = actionMap->getQAction(ActionData::EntityState);
    QAction* setRelationShipStateAction = actionMap->getQAction(ActionData::RelationShipState);
    //this->addAction(setPointerStateAction);
    this->addAction(setConnectStateAction);
    this->addAction(setAttributeStateAction);
    this->addAction(setEntityStateAction);
    this->addAction(setRelationShipStateAction);
}

AddDrawableToolBar::~AddDrawableToolBar(){
}