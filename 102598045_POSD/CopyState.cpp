#include "CopyState.h"
#include "ClipBoard.h"
#include "CommandFactory.h"
#include "CommandManager.h"
#include "HashMapUtil.h"
#include "Node.h"
#include "StringUtil.h"

CopyState::CopyState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate) : ClipBoardState(clipBoard,componentMap,componentIDVectorToOperate){
    for each(string componentID in componentIDVectorToOperate){
        if(componentMap.containsKey(componentID))
            this->componentMapToCopy.put(componentID,componentMap.get(componentID));
    }
    this->flag = false;
    this->executeCount = 0;
}

CopyState::~CopyState(){
    if(!this->flag)
        HashMapUtil::deleteAll(this->clonedComponentMap);
}

void CopyState::copy(CommandManager* commandManager){
    this->executeCount++;
    if(componentMapToCopy.empty())
        return;
    //clone component to copy
    HashMap<string,Component*> componentMapToCopyBuffer;
    for each(Node* node in this->componentMapToCopy){
        Component* component = node->clone();
        Point currentPosition = node->getRect().getPosition();
        component->setPosition(Point(currentPosition.getX()+20*this->executeCount,currentPosition.getY()+20*this->executeCount));
        componentMapToCopyBuffer.put(component->getID(),component);
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
    this->clonedComponentMap.clear();
    this->copy(commandManager);
    this->flag = true;
}