#include "DisplayTableInstruction.h"

void DisplayTableInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayTable();
}