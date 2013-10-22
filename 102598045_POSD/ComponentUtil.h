#pragma once

#include <vector>
#include <string>
#include "Attribute.h"
#include "Entity.h"

class ComponentUtil{
public:
	//template cant be put in cpp file
	template<typename type>
	static HashMap<string,type*> getConnectedNodeHashMapByType(HashMap<string,Component*> connectionHashMap);
	
	template<typename type>
	static HashMap<string,Component*> toComponentHashMap(HashMap<string,type*> typeHashMap);
	
	static void connectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
	static void disconnectWithEachOther(Component* firstNode,Component* secondNode,Component* connector);
};
//get component's connected node set by type
template<typename type>
static HashMap<string,type*> ComponentUtil::getConnectedNodeHashMapByType(HashMap<string,Component*> connectionHashMap){
	HashMap<string,type*> typeHashMap;
	for each(Component* connection in connectionHashMap){
		for each(Component* connectedNode in connection->getAllConnections()){
			if(typeid(*connectedNode).name() == typeid(type).name()){
				typeHashMap.put(connectedNode->getID(),static_cast<type*>(connectedNode));
			}
		}
	}
	return typeHashMap;
}

template<typename type>
static HashMap<string,Component*> ComponentUtil::toComponentHashMap(HashMap<string,type*> typeHashMap){
	HashMap<string,Component*> componentHashMap;
	for each(type* typePointer in typeHashMap){
		Component* component = typePointer;
		componentHashMap.put(component->getID(),component);	
	}
	return componentHashMap;
}