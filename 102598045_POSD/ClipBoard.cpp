#include "ClipBoard.h"

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