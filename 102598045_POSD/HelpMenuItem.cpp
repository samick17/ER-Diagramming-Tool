#include "HelpMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

HelpMenuItem::HelpMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::Help.c_str()));
    QAction* action = actionMap->getQAction(ActionData::About);
    this->addAction(action);
}

HelpMenuItem::~HelpMenuItem(){
}