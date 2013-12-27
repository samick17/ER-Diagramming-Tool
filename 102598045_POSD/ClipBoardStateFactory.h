#pragma once

#include "ClipBoardState.h"
#include "HashMap.h"

class Component;
class ClipBoard;

class ClipBoardStateFactory{
public:
    ClipBoardStateFactory();
    ~ClipBoardStateFactory();

    ClipBoardState* createState(int clipBoardStateID,ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVector);
};