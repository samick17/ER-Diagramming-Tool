#include "ClipBoard.h"
#include "Node.h"
#include "HashMapUtil.h"

ClipBoard::ClipBoard(){
}

ClipBoard::~ClipBoard(){
}

void ClipBoard::setData(HashMap<string,Component*> componentMap){
    this->componentMap = componentMap;
}

HashMap<string,Component*> ClipBoard::getData(){
    return this->componentMap;
}

void ClipBoard::clearData(){
    this->componentMap.clear();
}