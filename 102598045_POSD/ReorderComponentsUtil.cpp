#include "ReorderComponentsUtil.h"
#include "VectorUtil.h"
#include "StringUtil.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

ReorderComponentsUtil::ReorderComponentsUtil(){
}

ReorderComponentsUtil::~ReorderComponentsUtil(){
	for each (Component* component in this->orderedComponentMap)
		delete component;
}

HashMap<string,Component*> ReorderComponentsUtil::getReorderedComponentMap(ERModel* erModel){
	HashMap<string,Component*> orderedComponentVector = cloneComponentSet(erModel);

	//re-connect to the component, because of the cloned component use origin pointer	
	this->reConnectToComponentVector(orderedComponentVector);
	//enQueue all components & clear component vector
	queue<Component*> componentQueue;
	for each(Component* component in orderedComponentVector)
		componentQueue.push(component);
	orderedComponentVector.clear();

	//dequeue and reorder
	deueueAndInsertToVector(componentQueue,orderedComponentMap);

	return orderedComponentVector;
}

HashMap<string,Component*> ReorderComponentsUtil::cloneComponentSet(ERModel* erModel){	
	//avoid function call leads to memory leak, clear all elems first	
	for each (Component* component in this->orderedComponentMap)
		delete component;
	try{
		//clone set from erModel	
		for each(Component* component in erModel->getAllComponents()){
			Component* componentCloned = component->clone();
			this->orderedComponentMap.put(componentCloned->getID(),componentCloned);
		}
	}
	catch(Exception){
	}
	return this->orderedComponentMap;
}
//Although Cloned Component, its connection still connected to old Component
//So we must reConnect to Component in cloned Component Vector
void ReorderComponentsUtil::reConnectToComponentVector(HashMap<string,Component*> orderedComponentVector){	
	for each(Component* component in orderedComponentVector){
		for each(Component* connection in component->getAllConnections()){			
			//find Same ID in Cloned Vector			
			if(this->orderedComponentMap.containsKey(connection->getID())){
				Component* componentToConnect = this->orderedComponentMap.get(connection->getID());
				//disconnect to old connection
				component->disconnectTo(connection);
				//Connect to component we just found
				component->connectTo(componentToConnect);
			}
		}
	}
}
//dequeue all component & insert to component vector
//re set component id
void ReorderComponentsUtil::deueueAndInsertToVector(queue<Component*>& componentQueue,HashMap<string,Component*>& orderedComponentVector)
{
	int newID = 0;
	while(!componentQueue.empty()){
		Component* component = componentQueue.front();
		componentQueue.pop();

		component->setID(StringUtil::intToString(newID));
		orderedComponentVector.put(component->getID(),component);

		newID++;
	}
}