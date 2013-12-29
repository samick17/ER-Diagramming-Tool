#include "PasteComponentsCommand.h"
#include "Component.h"
#include "ClipBoard.h"
#include "HashMapUtil.h"
#include "StringUtil.h"
#include "WidgetDefaultSetting.h"

PasteComponentsCommand::PasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,int* newComponentID,int pasteCount) : componentMap(componentMap),clipBoard(clipBoard),newComponentID(newComponentID){
    for each(Component* component in this->clipBoard->getData()){
        //set component position
        Component* clonedComponent = component->clone();
        Point currentPosition = clonedComponent->getPosition();
        Point newPosition = Point(currentPosition.getX()+pasteCount*WidgetDefaultSetting::CloneOffsetX,currentPosition.getY()+pasteCount*WidgetDefaultSetting::CloneOffsetY);
        clonedComponent->setPosition(newPosition);
        this->componentMapToCopy.put(component->getID(),clonedComponent);
    }
}

PasteComponentsCommand::~PasteComponentsCommand(){
    if(!this->getExecutionFalg()){
        for each(Component* component in this->componentMapToCopy)
            (*this->newComponentID)--;
        HashMapUtil::deleteAll(this->componentMapToCopy);
    }
}

void PasteComponentsCommand::doExecute(){
    for each(Component* component in this->componentMapToCopy){
        component->setID(StringUtil::intToString(*this->newComponentID));
        this->componentMap.put(component->getID(),component);
        (*this->newComponentID)++;
    }
}

void PasteComponentsCommand::doUnExecute(){
    for each(Component* component in this->componentMapToCopy){
        this->componentMap.remove(component->getID());
        (*this->newComponentID)--;
    }
}