#include "ClipBoardState.h"

ClipBoardState::ClipBoardState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard) : erModel(erModel),componentMap(componentMap),clipBoard(clipBoard){
}

ClipBoardState::~ClipBoardState(){
}