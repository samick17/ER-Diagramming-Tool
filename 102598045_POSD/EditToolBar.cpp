#include "EditToolBar.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "GraphicalPresentation.h"

EditToolBar::EditToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    for(unsigned int actionIndex = ActionData::Undo;actionIndex <= ActionData::Paste;actionIndex++){
        QAction* openFileAction = actionMap->getQAction(actionIndex);
        this->addAction(openFileAction);
    }
    this->graphicalPresentation = graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserverToModel(this);
    this->connect(this,SIGNAL(onNotifyEvent()),this,SLOT(executeNotify()));
}

EditToolBar::~EditToolBar(){
    this->graphicalPresentation->unregisterObserverToModel(this);
}

void EditToolBar::notify(Subject* subject){
    this->onNotifyEvent();

}

void EditToolBar::refresh(){
    int offset = ActionData::Undo;
    this->actions().at(ActionData::Undo-offset)->setEnabled(this->graphicalPresentation->canUndo());
    this->actions().at(ActionData::Redo-offset)->setEnabled(this->graphicalPresentation->canRedo());
    this->actions().at(ActionData::Delete-offset)->setEnabled(this->graphicalPresentation->isAnyWidgetSelected());
    this->actions().at(ActionData::Cut-offset)->setEnabled(this->graphicalPresentation->isAnyWidgetSelected());
    this->actions().at(ActionData::Copy-offset)->setEnabled(this->graphicalPresentation->isAnyWidgetSelected());
    this->actions().at(ActionData::Paste-offset)->setEnabled(this->graphicalPresentation->canPasteWidgets());
}

void EditToolBar::executeNotify(){
    this->mutex.lock();
    this->refresh();
    this->mutex.unlock();
}