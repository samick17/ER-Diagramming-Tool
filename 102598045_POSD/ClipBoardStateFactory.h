#pragma once

#include "ClipBoardState.h"
#include "HashMap.h"

class ERModel;
class Component;
class ClipBoard;

typedef ClipBoardState* (*NewClipBoardStateFunction)(int clipBoardStateID,ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);

class ClipBoardStateFactory{
public:
    ClipBoardStateFactory();
    ~ClipBoardStateFactory();

    ClipBoardState* createState(int clipBoardStateID,ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);
private:
    template <typename Type>
    static ClipBoardState* newState(int clipBoardStateID,ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard);

    NewClipBoardStateFunction findNewStateFunction(int clipBoardStateID);
    HashMap<int,NewClipBoardStateFunction> newStateMap;
};

template <typename Type>
ClipBoardState* ClipBoardStateFactory::newState(int clipBoardStateID,ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard){
    return new Type(erModel,componentMap,clipBoard);
}