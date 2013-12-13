#include "MoveComponentsCommand.h"

MoveComponentsCommand::MoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition) : selectedComponentMap(selectedComponentMap),mousePressPosition(mousePressPosition),mouseReleasePosition(mouseReleasePosition){
}

MoveComponentsCommand::~MoveComponentsCommand(){
}

void MoveComponentsCommand::doExecute(){
}

void MoveComponentsCommand::doUnExecute(){
}