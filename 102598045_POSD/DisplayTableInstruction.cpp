#include "DisplayTableInstruction.h"
#include "ControllerEvent.h"

void DisplayTableInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayTable();
	textPresentation->notify(ControllerEvent::DisplayTable);
}