#include "RedoInstruction.h"
#include "ControllerEvent.h"

void RedoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->redo();
    cout<<"Redo succeed."<<endl;
    textPresentation->sync(ControllerEvent::Redo);
}