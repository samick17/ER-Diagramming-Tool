#include "ClipBoard.h"
#include "Node.h"
#include "HashMapUtil.h"

ClipBoard::ClipBoard(){
}

ClipBoard::~ClipBoard(){
    HashMapUtil::deleteAll(this->componentMap);
}

void ClipBoard::setData(HashMap<string,Component*> componentMap){
    HashMapUtil::deleteAll(this->componentMap);
    for each(Component* component in componentMap)
        this->componentMap.put(component->getID(),component->clone());
}

HashMap<string,Component*> ClipBoard::getData(){
    return this->componentMap;
}

void ClipBoard::clearData(){
    HashMapUtil::deleteAll(this->componentMap);
}