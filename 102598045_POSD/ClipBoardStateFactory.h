#pragma once

#include "ClipBoardState.h"
#include "HashMap.h"

class GraphicalPresentation;

typedef ClipBoardState* (*NewClipBoardStateFunction)(int clipBoardStateID,ERModel* erModel);

class ClipBoardStateFactory{
public:
    ClipBoardStateFactory();
    ~ClipBoardStateFactory();

    ClipBoardState* createState(int clipBoardStateID,ERModel* erModel);
private:
    template <typename Type>
    static ClipBoardState* newState(int clipBoardStateID,ERModel* erModel);

    NewClipBoardStateFunction findNewStateFunction(int clipBoardStateID);
    HashMap<int,NewClipBoardStateFunction> newStateMap;
};

template <typename Type>
ClipBoardState* ClipBoardStateFactory::newState(int clipBoardStateID,ERModel* erModel){
    return new Type(erModel);
}