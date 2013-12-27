#include "PasteComponentsCommand.h"
#include "Component.h"
#include "ClipBoard.h"
#include "HashMapUtil.h"

PasteComponentsCommand::PasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard) : componentMap(componentMap),clipBoard(clipBoard){
    this->componentMapToCopy = clipBoard->getData();
}

PasteComponentsCommand::~PasteComponentsCommand(){
    if(!this->getExecutionFalg())
        HashMapUtil::deleteAll(this->componentMapToCopy);
}

void PasteComponentsCommand::doExecute(){
    for each(Component* component in this->componentMapToCopy)
        this->componentMap.put(component->getID(),component);
}

void PasteComponentsCommand::doUnExecute(){
    for each(Component* component in this->componentMapToCopy)
        this->componentMap.remove(component->getID());
}