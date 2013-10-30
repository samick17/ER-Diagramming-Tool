#include "UndoInstruction.h"

UndoInstruction::UndoInstruction(){
}

UndoInstruction::~UndoInstruction(){
}

void UndoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->undo();
    cout<<"Undo succeed."<<endl;
    textUIPresenter->displayComponents();
    textUIPresenter->displayConnections();
}