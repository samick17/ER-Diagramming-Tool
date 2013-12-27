#pragma once

#include "ClipBoardState.h"
#include "HashMap.h"

class Component;
class ClipBoard;

typedef ClipBoardState* (*NewClipBoardStateFunction)(int clipBoardStateID,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVector);

class ClipBoardStateFactory{
public:
    ClipBoardStateFactory();
    ~ClipBoardStateFactory();

    ClipBoardState* createState(int clipBoardStateID,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVector);
private:
    template <typename Type>
    static ClipBoardState* newState(int clipBoardStateID,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVector);

    NewClipBoardStateFunction findNewStateFunction(int clipBoardStateID);
    HashMap<int,NewClipBoardStateFunction> newStateMap;
};

template <typename Type>
ClipBoardState* ClipBoardStateFactory::newState(int clipBoardStateID,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVector){
    return new Type(componentMap,clipBoard,componentIDVector);
}