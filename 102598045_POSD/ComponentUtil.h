#pragma once

#include <vector>
#include <string>
#include "Attribute.h"
#include "Entity.h"

class ComponentUtil{
public:
	//template cant be put in cpp file
	template<typename Type>
	static HashMap<string,Type*> getConnectedNodeHashMapByType(HashMap<string,Component*> connectionHashMap);
	
	template<typename Type>
	static HashMap<string,Component*> toComponentHashMap(HashMap<string,Type*> typeHashMap);
	
	static void connectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
	static void disconnectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
};
//get component's connected node set by type
template<typename Type>
static HashMap<string,Type*> ComponentUtil::getConnectedNodeHashMapByType(HashMap<string,Component*> connectionHashMap){
	HashMap<string,Type*> typeHashMap;
	for each(Component* connection in connectionHashMap)
		for each(Component* connectedNode in connection->getAllConnections())
			if(typeid(*connectedNode).name() == typeid(Type).name())
				typeHashMap.put(connectedNode->getID(),static_cast<Type*>(connectedNode));	
	return typeHashMap;
}
//convert all concrete component to base class
template<typename Type>
static HashMap<string,Component*> ComponentUtil::toComponentHashMap(HashMap<string,Type*> typeHashMap){
	HashMap<string,Component*> componentHashMap;
	for each(Type* typePointer in typeHashMap){
		Component* component = typePointer;
		componentHashMap.put(component->getID(),component);	
	}
	return componentHashMap;
}