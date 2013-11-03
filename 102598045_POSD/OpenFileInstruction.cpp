#include "OpenFileInstruction.h"

void OpenFileInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"Please input the file name: "<<endl;
    string filePath = textPresentation->getInput();
    textPresentation->openFile(filePath);
    textUIPresenter->displayDiagram();
}