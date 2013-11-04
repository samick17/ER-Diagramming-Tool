#include "DeleteComponentInstruction.h"
#include "ControllerEvent.h"

void DeleteComponentInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    //find node to be connect
    cout<<"Please enter the component ID"<<endl;
    Component* componentToDelete = textPresentation->findComponent();
    textPresentation->deleteComponent(componentToDelete);
    cout<<"The component '"+componentToDelete->getID()+"' has been deleted. "<<endl;
	textPresentation->notify(ControllerEvent::DeleteComponent);
}