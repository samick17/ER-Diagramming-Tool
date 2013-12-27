#include "ClipBoardState.h"

ClipBoardState::ClipBoardState(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,vector<string> componentIDVectorToOperate) : componentMap(componentMap),clipBoard(clipBoard),componentIDVectorToOperate(componentIDVectorToOperate){
}

ClipBoardState::~ClipBoardState(){
}