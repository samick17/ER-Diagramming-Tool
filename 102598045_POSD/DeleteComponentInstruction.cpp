#include "DeleteComponentInstruction.h"
#include "ControllerEvent.h"

void DeleteComponentInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayComponents();
    //find node to be connect
    cout<<"Please enter the component ID"<<endl;
    string componentID;
    while(true){
        try{
            componentID = textPresentation->getInput();
            textPresentation->deleteComponent(componentID);
            break;
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    cout<<"The component '"+componentID+"' has been deleted. "<<endl;
    textPresentation->sync(ControllerEvent::DeleteComponent);
}