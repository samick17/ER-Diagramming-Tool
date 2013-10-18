#pragma once

#include <vector>
#include "HashMap.h"
#include "Component.h"

class ERModelUtil{
public:
	//template cant be put in cpp file
	template<typename type> 
	static HashMap<string,type*> convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap);	
};
//convert component hashmap to concrete type hashmap
template<typename type> 
static HashMap<string,type*> ERModelUtil::convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap){
	HashMap<string,type*> typeHashMap;
	for each (Component* component in componentHashMap){	
		if(typeid(*component).name() == typeid(type).name()){
			typeHashMap.put(component->getID(),static_cast<type*>(component));
		}
	}
	return typeHashMap;
}