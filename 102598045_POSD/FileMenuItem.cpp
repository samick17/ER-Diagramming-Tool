#include "FileMenuItem.h"
#include "ActionData.h"
#include "MenuSetting.h"

FileMenuItem::FileMenuItem(QActionMap* actionMap,QWidget* parent) : QMenu(parent){
    this->setTitle(QString(MenuSetting::File.c_str()));
    QAction* openFileAction = actionMap->getQAction(ActionData::OpenFile);
    QAction* exitAction = actionMap->getQAction(ActionData::Exit);

    this->addAction(openFileAction);
    this->addAction(exitAction);
}

FileMenuItem::~FileMenuItem(){
}