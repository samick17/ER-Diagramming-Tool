#include "DisplayDiagramInstruction.h"
#include "ControllerEvent.h"

void DisplayDiagramInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayDiagram();
	textPresentation->sync(ControllerEvent::DisplayDiagram);
}