#include "SetPointerWidget.h"
#include "ActionData.h"

SetPointerWidget::SetPointerWidget(QActionMap* actionMap,QWidget* parent) : QToolButton(parent){
    QAction* setPointerStateAction = actionMap->getQAction(ActionData::PointerState);
    this->addAction(setPointerStateAction);
    this->setIcon(setPointerStateAction->icon());
    this->setCheckable(true);
}

SetPointerWidget::~SetPointerWidget(){
}