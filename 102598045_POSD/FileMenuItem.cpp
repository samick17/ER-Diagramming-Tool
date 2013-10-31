#include "FileMenuItem.h"
#include "TextPresentation.h"
#include "GraphicalUI.h"
#include "ActionData.h"

FileMenuItem::FileMenuItem(QActionMap* actionMap){
    this->setTitle(QString("File"));
    QAction* openFileAction = actionMap->getQAction(ActionData::OpenFile);
    QAction* exitAction = actionMap->getQAction(ActionData::Exit);

    this->addAction(openFileAction);
    this->addAction(exitAction);
}

FileMenuItem::~FileMenuItem(){
}