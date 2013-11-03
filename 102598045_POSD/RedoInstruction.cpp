#include "RedoInstruction.h"

void RedoInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->redo();
    cout<<"Redo succeed."<<endl;
    textUIPresenter->displayComponents();
    textUIPresenter->displayConnections();
}