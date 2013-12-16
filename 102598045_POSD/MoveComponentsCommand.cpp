#include "MoveComponentsCommand.h"

MoveComponentsCommand::MoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition) : selectedComponentMap(selectedComponentMap),mousePressPosition(mousePressPosition),mouseReleasePosition(mouseReleasePosition){
    this->deltaPosition = mouseReleasePosition-mousePressPosition;
    //this->doUnExecute();
}

MoveComponentsCommand::~MoveComponentsCommand(){
}

void MoveComponentsCommand::doExecute(){
    for each(Component* component in selectedComponentMap){
        Point position = component->getRect().getPosition();
        component->setPosition(position+this->deltaPosition);
    }
}

void MoveComponentsCommand::doUnExecute(){
    for each(Component* component in selectedComponentMap){
        Point position = component->getRect().getPosition();
        component->setPosition(position-this->deltaPosition);
    }
}