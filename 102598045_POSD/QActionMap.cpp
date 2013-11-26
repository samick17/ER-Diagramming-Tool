#include "QActionMap.h"
#include "GraphicalUI.h"
#include "ActionData.h"

QActionMap::QActionMap(GraphicalUI* graphicalUI){
    //initial all action
    for (unsigned int index = 0;index < ActionData::ActionLength;index++)
        this->putQAction(QActionData(index),graphicalUI);
}

QActionMap::~QActionMap(){
}

QAction* QActionMap::getQAction(unsigned int index){
    return this->actionMap.get(index);
}

void QActionMap::putQAction(QActionData qActionData,GraphicalUI* graphicalUI){
    QAction* openFileAction = new QAction(QIcon(QString(qActionData.getIconPath().c_str())),QString(qActionData.getActionText().c_str()),graphicalUI);
    QKeySequence keySequence = QKeySequence(qActionData.getKeySequence().c_str());
    openFileAction->setShortcut(keySequence);
    this->actionMap.put(qActionData.getActionIndex(),openFileAction);
}