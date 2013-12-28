#include "PasteComponentsCommand.h"
#include "Component.h"
#include "ClipBoard.h"
#include "HashMapUtil.h"
#include "ClipBoardState.h"
#include "StringUtil.h"

PasteComponentsCommand::PasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,ClipBoardState* clipBoardState,int* newComponentID) : componentMap(componentMap),clipBoard(clipBoard),clipBoardState(clipBoardState),newComponentID(newComponentID){
    for each(Component* component in this->clipBoard->getData()){
        this->componentMapToCopy.put(component->getID(),component->clone());
    }
}

PasteComponentsCommand::~PasteComponentsCommand(){
    if(!this->getExecutionFalg()){
        for each(Component* component in this->componentMapToCopy)
            *this->newComponentID--;
        HashMapUtil::deleteAll(this->componentMapToCopy);
    }
}

void PasteComponentsCommand::doExecute(){
    for each(Component* component in this->componentMapToCopy){
        component->setID(StringUtil::intToString(*this->newComponentID));
        this->componentMap.put(component->getID(),component);
        *this->newComponentID++;
    }
    this->clipBoardState->paste();
}

void PasteComponentsCommand::doUnExecute(){
    for each(Component* component in this->componentMapToCopy){
        this->componentMap.remove(component->getID());
        *this->newComponentID--;
    }
}