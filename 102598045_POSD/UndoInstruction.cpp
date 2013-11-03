#include "UndoInstruction.h"

void UndoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->undo();
    cout<<"Undo succeed."<<endl;
    textUIPresenter->displayComponents();
    textUIPresenter->displayConnections();
}