#include "CutState.h"
#include "ERModel.h"
#include "ClipBoardStateID.h"
#include "CommandFactory.h"

CutState::CutState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard) : ClipBoardState(erModel,componentMap,clipBoard){
}

CutState::~CutState(){
}

bool CutState::canPaste(){
    return true;
}

void CutState::paste(CommandManager* commandManager){
    HashMap<string,Component*> componentMapToCopy = clipBoard->getData();
    CommandFactory commandFactory;
    Command* command = commandFactory.createPasteComponentsCommand(this->componentMap,clipBoard);
    commandManager->execute(command);
    this->clipBoard->clearData();
}