#include "CopyState.h"
#include "ClipBoard.h"
#include "CommandFactory.h"
#include "CommandManager.h"

CopyState::CopyState(ERModel* erModel,HashMap<string,Component*>& componentMap,ClipBoard* clipBoard) : ClipBoardState(erModel,componentMap,clipBoard){
}

CopyState::~CopyState(){
}

bool CopyState::canPaste(){
    return true;
}

void CopyState::paste(CommandManager* commandManager){
    HashMap<string,Component*> componentMapToCopy = clipBoard->getData();
	//componentFactory create component
    CommandFactory commandFactory;
    Command* command = commandFactory.createPasteComponentsCommand(this->componentMap,clipBoard);
    commandManager->execute(command);
}//paste undo