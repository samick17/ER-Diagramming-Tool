#include "DisplayTableInstruction.h"
#include "ControllerEvent.h"

void DisplayTableInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->sync(ControllerEvent::DisplayTable);
}