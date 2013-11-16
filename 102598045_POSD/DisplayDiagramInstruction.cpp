#include "DisplayDiagramInstruction.h"
#include "ControllerEvent.h"

void DisplayDiagramInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
	textPresentation->sync(ControllerEvent::DisplayDiagram);
}