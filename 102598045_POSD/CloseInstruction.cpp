#include "CloseInstruction.h"
#include "ControllerEvent.h"
#include "SaveFileInstruction.h"

void CloseInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    if(textPresentation->isNeedToSave()){
        while(true){
            textUIPresenter->logMessage("Do you want to save file?(y/n)",true);
            string input = textPresentation->getInput();
            if(input == "Y" || input == "y"){
                try{
                    SaveFileInstruction saveFileInstruction;
                    saveFileInstruction.execute(textPresentation,textUIPresenter);
                    break;
                }
                catch(Exception& exception){
                    textUIPresenter->logMessage(exception.what(),true);
                }
            }
            else{
                break;
            }
        }
    }
    cout<<"GooBye!"<<endl;
    textPresentation->close();
}