#include "AddMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

AddMenuItem::AddMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::Add.c_str()));
    QAction* pointerStateAction = actionMap->getQAction(ActionData::PointerState);
    QAction* connectStateAction = actionMap->getQAction(ActionData::ConnectState);
    QAction* addAttributeState = actionMap->getQAction(ActionData::AttributeState);
    QAction* addEntityState = actionMap->getQAction(ActionData::EntityState);
    QAction* addRelationShipState = actionMap->getQAction(ActionData::RelationShipState);

    this->addAction(pointerStateAction);
    this->addAction(connectStateAction);
    this->addAction(addAttributeState);
    this->addAction(addEntityState);
    this->addAction(addRelationShipState);
}

AddMenuItem::~AddMenuItem(){
}