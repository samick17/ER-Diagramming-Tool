#include "DeleteComponentInstruction.h"
#include "ControllerEvent.h"

void DeleteComponentInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayComponents();
    //find node to be connect
    cout<<"Please enter the component ID"<<endl;
    string input;
    while(true){
        try{
            input = textPresentation->getInput();
            textPresentation->deleteComponent(input);
            break;
        }
        catch(Exception& exception){
            cout<<exception.what()<<endl;
        }
    }
    cout<<"The component '"+input+"' has been deleted. "<<endl;
    textPresentation->sync(ControllerEvent::DeleteComponent);
}