#include "FileToolBar.h"
#include "ActionData.h"

FileToolBar::FileToolBar(QActionMap* actionMap,QWidget* parent) : QToolBar(parent){
    QAction* openFileAction = actionMap->getQAction(ActionData::OpenFile);
    QAction* exitAction = actionMap->getQAction(ActionData::Exit);
    this->addAction(openFileAction);
    this->addAction(exitAction);
}

FileToolBar::~FileToolBar(){
}