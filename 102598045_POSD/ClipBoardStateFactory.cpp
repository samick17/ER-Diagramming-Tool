#include "ClipBoardStateFactory.h"
#include "ClipBoardStateID.h"
#include "NullClipBoardState.h"
#include "CutState.h"
#include "CopyState.h"

ClipBoardStateFactory::ClipBoardStateFactory(){
    this->newStateMap.put(ClipBoardStateID::NullClipBoardState,newState<NullClipBoardState>);
    this->newStateMap.put(ClipBoardStateID::CutState,newState<CutState>);
    this->newStateMap.put(ClipBoardStateID::CopyState,newState<CopyState>);
}

ClipBoardStateFactory::~ClipBoardStateFactory(){
}

ClipBoardState* ClipBoardStateFactory::createState(int clipBoardStateID,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVector){
    NewClipBoardStateFunction newStateFunction = this->findNewStateFunction(clipBoardStateID);
    return newStateFunction(clipBoardStateID,componentMap,clipBoard,componentIDVector);
}

NewClipBoardStateFunction ClipBoardStateFactory::findNewStateFunction(int clipBoardStateID){
    return this->newStateMap.get(clipBoardStateID);
}