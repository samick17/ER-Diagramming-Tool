#include "FileToolBar.h"
#include "ActionData.h"

FileToolBar::FileToolBar(QActionMap* actionMap,QWidget* parent) : QToolBar(parent){
    for(unsigned int actionIndex = ActionData::OpenFile;actionIndex <= ActionData::Delete;actionIndex++){
        QAction* openFileAction = actionMap->getQAction(actionIndex);
        this->addAction(openFileAction);
    }
}

FileToolBar::~FileToolBar(){
}