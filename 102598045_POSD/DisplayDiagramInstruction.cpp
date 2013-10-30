#include "DisplayDiagramInstruction.h"

DisplayDiagramInstruction::DisplayDiagramInstruction(){
}

DisplayDiagramInstruction::~DisplayDiagramInstruction(){
}

void DisplayDiagramInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayDiagram();
}