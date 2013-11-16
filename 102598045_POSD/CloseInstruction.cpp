#include "CloseInstruction.h"
#include "ControllerEvent.h"

void CloseInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"GooBye!"<<endl;
    textPresentation->close();
}