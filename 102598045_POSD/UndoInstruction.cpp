#include "UndoInstruction.h"
#include "ControllerEvent.h"

void UndoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->undo();
    cout<<"Undo succeed."<<endl;
    textPresentation->sync(ControllerEvent::Undo);
}