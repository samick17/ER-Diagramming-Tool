#include "SaveFileInstruction.h"

SaveFileInstruction::SaveFileInstruction(){
}

SaveFileInstruction::~SaveFileInstruction(){
}

void SaveFileInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"Please input the file name: "<<endl;
    string filePath = textPresentation->getInput();
    textPresentation->saveFile(filePath);
}