#include "EditMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

EditMenuItem::EditMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::Edit.c_str()));
    for(unsigned int index = ActionData::Undo; index <= ActionData::Paste;index++){
        QAction* action = actionMap->getQAction(index);
        this->addAction(action);
    }
}

EditMenuItem::~EditMenuItem(){
}