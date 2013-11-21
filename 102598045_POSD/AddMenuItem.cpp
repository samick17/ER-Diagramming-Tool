#include "AddMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

AddMenuItem::AddMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::Add.c_str()));
    for(unsigned int index = ActionData::Undo; index <= ActionData::SetPrimaryKeyState;index++){
        QAction* action = actionMap->getQAction(index);
        this->addAction(action);
    }
}

AddMenuItem::~AddMenuItem(){
}