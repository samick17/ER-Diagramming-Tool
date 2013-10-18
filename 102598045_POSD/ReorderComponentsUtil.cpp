#include "ReorderComponentsUtil.h"
#include "VectorUtil.h"
#include "StringUtil.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

ReorderComponentsUtil::ReorderComponentsUtil(){
}

ReorderComponentsUtil::~ReorderComponentsUtil(){
	VectorUtil::deleteAllElementsInVector(this->reorderedComponentVector);	
}

vector<Component*> ReorderComponentsUtil::getReorderedComponentVector(ERModel* erModel){
	vector<Component*> orderedComponentVector = cloneComponentSet(erModel);

	//re-connect to the component, because of the cloned component use origin pointer	
	reConnectToComponentVector(orderedComponentVector);
	//enQueue all components & clear component vector
	queue<Component*> componentQueue;
	for each(Component* component in orderedComponentVector)
		componentQueue.push(component);
	orderedComponentVector.clear();

	//dequeue and reorder
	deueueAndInsertToVector(componentQueue,orderedComponentVector);

	return orderedComponentVector;
}

vector<Component*> ReorderComponentsUtil::cloneComponentSet(ERModel* erModel){	
	//avoid function call leads to memory leak, clear all elems first	
	VectorUtil::deleteAllElementsInVector(this->reorderedComponentVector);
	try{
		//clone set from erModel	
		for each(Component* component in erModel->getAllComponents())
			this->reorderedComponentVector.push_back(component->clone());
	}
	catch(Exception){
	}
	return this->reorderedComponentVector;
}
//Although Cloned Component, its connection still connected to old Component
//So we must reConnect to Component in cloned Component Vector
void ReorderComponentsUtil::reConnectToComponentVector(vector<Component*> orderedComponentVector){	
	for each(Component* component in orderedComponentVector){
		for each(Component* connection in component->getAllConnections()){			
			//find Same ID in Cloned Vector
			Component* componentToConnect = ComponentUtil::getComponentByIDInVector(orderedComponentVector,connection->getID());			
			//disconnect to old connection
			component->disconnectTo(connection);
			//Connect to component we just found
			component->connectTo(componentToConnect);
		}
	}
}
//dequeue all component & insert to component vector
//re set component id
void ReorderComponentsUtil::deueueAndInsertToVector(queue<Component*>& componentQueue,vector<Component*>& orderedComponentVector)
{
	int newID = 0;
	while(!componentQueue.empty()){
		Component* component = componentQueue.front();
		componentQueue.pop();

		component->setID(StringUtil::intToString(newID));
		orderedComponentVector.push_back(component);

		newID++;
	}
}