#pragma once

#include <set>
#include <vector>
#include <string>
#include "Attribute.h"
#include "Entity.h"

class ComponentUtil{
public:
	//template cant be put in cpp file
	template<typename type>
	static set<type*> getConnectedNodeSetByType(set<Component*> connectionSet);
	
	template<typename type>
	static set<Component*> toComponentSet(set<type*> typeSet);
	
	static Component* getComponentByIDInVector(vector<Component*> componentVector,string id);
	static void connectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
	static void disconnectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
};
//get component's connected node set by type
template<typename type>
static set<type*> ComponentUtil::getConnectedNodeSetByType(set<Component*> connectionSet){
	set<type*> typeSet;
	for each(Component* connection in connectionSet){
		for each(Component* connectedNode in connection->getAllConnectors()){
			if(typeid(*connectedNode).name() == typeid(type).name())
			{
				typeSet.insert(static_cast<type*>(connectedNode));
			}
		}
	}
	return typeSet;
}
//convert concrete type to component type
template<typename type>
static set<Component*> ComponentUtil::toComponentSet(set<type*> typeSet){
	set<Component*> componentSet;
	for each(type* typePointer in typeSet){			
		componentSet.insert(typePointer);	
	}
	return componentSet;
}