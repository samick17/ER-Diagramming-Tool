#include "CopyState.h"
#include "ClipBoard.h"
#include "CommandFactory.h"
#include "CommandManager.h"
#include "HashMapUtil.h"
#include "Node.h"
#include "StringUtil.h"

CopyState::CopyState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate) : ClipBoardState(componentMap,clipBoard,componentIDVectorToOperate){
    for each(string componentID in componentIDVectorToOperate){
        if(componentMap.containsKey(componentID))
            this->componentMapToCopy.put(componentID,componentMap.get(componentID));
    }
    this->flag = false;
}

CopyState::~CopyState(){
    if(!this->flag)
        HashMapUtil::deleteAll(this->clonedComponentMap);
}

bool CopyState::canPaste(){
    return true;
}

void CopyState::copy(CommandManager* commandManager,int* newComponentID){
    this->newComponentID = newComponentID;
    if(componentMapToCopy.empty())
        return;
    //clone component to copy
    HashMap<string,Component*> componentMapToCopyBuffer;
    int newComponentIDBuffer = *newComponentID;
    for each(Node* node in this->componentMapToCopy){
        Component* component = node->clone();
        component->setID(StringUtil::intToString(*this->newComponentID));
        componentMapToCopyBuffer.put(component->getID(),component);
        this->newComponentID++;
    }
    if(componentMapToCopyBuffer.empty()){
        *this->newComponentID = newComponentIDBuffer;
        return;
    }
    this->clonedComponentMap = componentMapToCopyBuffer;
    //set clipBoard data from cloned componentMap
    this->clipBoard->setData(this->clonedComponentMap);
}

void CopyState::paste(CommandManager* commandManager){
    //componentFactory create component
    CommandFactory commandFactory;
    Command* command = commandFactory.createPasteComponentsCommand(this->componentMap,clipBoard);
    commandManager->execute(command);
    this->copy(commandManager,this->newComponentID);
    this->flag = true;
}