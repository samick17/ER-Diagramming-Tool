#include "ClipBoardStateFactory.h"
#include "ClipBoardStateID.h"
#include "NullClipBoardState.h"
#include "CutState.h"
#include "CopyState.h"

ClipBoardStateFactory::ClipBoardStateFactory(){
}

ClipBoardStateFactory::~ClipBoardStateFactory(){
}

ClipBoardState* ClipBoardStateFactory::createState(int clipBoardStateID,ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVector){
    if(clipBoardStateID == ClipBoardStateID::CutState)
        return new CutState(clipBoard,componentMap,componentIDVector);
    else if(clipBoardStateID == ClipBoardStateID::CopyState)
        return new CopyState(clipBoard,componentMap,componentIDVector);
    return new NullClipBoardState(clipBoard,componentMap,componentIDVector);
}