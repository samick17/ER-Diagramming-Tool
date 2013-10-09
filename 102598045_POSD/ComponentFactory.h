#pragma once

#include "Component.h"
#include <hash_map>
#include "ComponentType.h"

typedef Component* (*NewComponentFunc)(ComponentData);
typedef pair<string,NewComponentFunc> NewComponentFuncPair;

class ComponentFactory{
public:
	ComponentFactory();
	~ComponentFactory();

	Component* createComponent(string componentType);
	void resetFactory();
private:
	static int count;
	hash_map<string,NewComponentFunc> newComponentMap;	
	NewComponentFunc findNewComponentFunction(string componentType);
	template <typename type>
	static Component* newComponent(ComponentData componentData){
		return new type(componentData);
	}
};