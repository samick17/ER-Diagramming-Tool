#include "ReorderComponentsUtil.h"
#include "StringUtil.h"
#include "ERModelUtil.h"
#include "ComponentUtil.h"

ReorderComponentsUtil::ReorderComponentsUtil(){
}

ReorderComponentsUtil::~ReorderComponentsUtil(){
	this->clearComponentMap();
}

HashMap<string,Component*> ReorderComponentsUtil::getReorderedComponentMap(ERModel* erModel){
	
	this->cloneComponentSet(erModel);
	//re-connect to the component, because of the cloned component use origin pointer	
	this->reConnectToComponentVector();
	//enQueue all components & clear component vector
	queue<Component*> componentQueue;
	for each(Component* component in this->componentMap)
		componentQueue.push(component);

	//dequeue and reorder
	return this->dequeueAndInsertToVector(componentQueue);
}

void ReorderComponentsUtil::clearComponentMap(){
	for each (Component* component in this->componentMap){
		delete component;
	}
	this->componentMap.clear();
}

HashMap<string,Component*> ReorderComponentsUtil::cloneComponentSet(ERModel* erModel){	
	//avoid function call leads to memory leak, clear all elems first	
	this->clearComponentMap();
	try{
		//clone set from erModel	
		for each(Component* component in erModel->getAllComponents()){
			Component* componentCloned = component->clone();
			this->componentMap.put(componentCloned->getID(),componentCloned);
		}
	}
	catch(Exception){
	}
	return this->componentMap;
}
//Although Cloned Component, its connection still connected to old Component
//So we must reConnect to Component in cloned Component Vector
void ReorderComponentsUtil::reConnectToComponentVector(){	
	for each(Component* component in this->componentMap){
		for each(Component* connection in component->getAllConnections()){			
			//find Same ID in Cloned Vector			
			if(this->componentMap.containsKey(connection->getID())){
				Component* componentToConnect = this->componentMap.get(connection->getID());
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
HashMap<string,Component*> ReorderComponentsUtil::dequeueAndInsertToVector(queue<Component*>& componentQueue)
{
	HashMap<string,Component*> orderedComponentMap;
	int newID = 0;
	while(!componentQueue.empty()){
		Component* component = componentQueue.front();
		componentQueue.pop();

		component->setID(StringUtil::intToString(newID));
		
		orderedComponentMap.put(component->getID(),component);
		
		newID++;
	}
	return orderedComponentMap;
}