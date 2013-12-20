#include "FileMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

FileMenuItem::FileMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::File.c_str()));
    for(unsigned int actionIndex = ActionData::OpenFile;actionIndex <= ActionData::Exit;actionIndex++)
        this->addAction(actionMap->getQAction(actionIndex));
}

FileMenuItem::~FileMenuItem(){
}