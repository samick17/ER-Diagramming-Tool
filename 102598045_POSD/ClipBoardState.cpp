#include "ClipBoardState.h"

ClipBoardState::ClipBoardState(ClipBoard* clipBoard,HashMap<string,Component*>& componentMap,vector<string> componentIDVectorToOperate) : clipBoard(clipBoard),componentMap(componentMap),componentIDVectorToOperate(componentIDVectorToOperate){
}

ClipBoardState::~ClipBoardState(){
}