#include "CloseInstruction.h"

CloseInstruction::CloseInstruction(){
}

CloseInstruction::~CloseInstruction(){
}

void CloseInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"GooBye!"<<endl;
    textPresentation->close();
}