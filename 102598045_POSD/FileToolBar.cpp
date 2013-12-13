#include "FileToolBar.h"
#include "ActionData.h"
#include "GraphicalUI.h"

FileToolBar::FileToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    for(unsigned int actionIndex = ActionData::OpenFile;actionIndex <= ActionData::Exit;actionIndex++){
        QAction* openFileAction = actionMap->getQAction(actionIndex);
        this->addAction(openFileAction);
    }
}

FileToolBar::~FileToolBar(){
}