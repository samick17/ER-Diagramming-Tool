#include "SaveFileInstruction.h"

void SaveFileInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"Please input the file name: "<<endl;
    string filePath = textPresentation->getInput();
    textPresentation->saveFile(filePath);
}