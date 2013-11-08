#include "RedoInstruction.h"
#include "ControllerEvent.h"

void RedoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->redo();
    cout<<"Redo succeed."<<endl;
    textUIPresenter->displayComponents();
    textUIPresenter->displayConnections();
	textPresentation->sync(ControllerEvent::DisplayDiagram);
}