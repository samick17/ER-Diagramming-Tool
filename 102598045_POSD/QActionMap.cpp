#include "QActionMap.h"
#include "GraphicalUI.h"
#include "ActionData.h"

QActionMap::QActionMap(GraphicalUI* graphicalUI){
    this->putQAction(QActionData(ActionData::OpenFile,ActionData::OpenFileIconPath,ActionData::OpenFileShortCutKey),graphicalUI);
    this->putQAction(QActionData(ActionData::Exit,ActionData::ExitIconPath,ActionData::ExitShortCutKey),graphicalUI);
}

QActionMap::~QActionMap(){
}

QAction* QActionMap::getQAction(string actionText){
    return this->actionMap.get(actionText);
}

void QActionMap::putQAction(QActionData qActionData,GraphicalUI* graphicalUI){
    QAction* openFileAction = new QAction(QIcon(QString(qActionData.getIconPath().c_str())),QString(qActionData.getActionText().c_str()),graphicalUI);
    openFileAction->setShortcut(qActionData.getKeySequence());
    this->actionMap.put(qActionData.getActionText(),openFileAction);
}