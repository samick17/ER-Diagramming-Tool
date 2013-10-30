#include "DisplayTableInstruction.h"

DisplayTableInstruction::DisplayTableInstruction(){
}

DisplayTableInstruction::~DisplayTableInstruction(){
}

void DisplayTableInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayTable();
}