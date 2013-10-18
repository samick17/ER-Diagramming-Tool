#pragma once

#include "Component.h"
#include "HashMap.h"
#include "ComponentType.h"

typedef Component* (*NewComponentFunc)(ComponentData);

class ComponentFactory{
public:
	ComponentFactory();
	~ComponentFactory();

	Component* createComponent(string componentType);
	void resetFactory();
private:
	static int count;
	HashMap<string,NewComponentFunc> newComponentMap;	
	NewComponentFunc findNewComponentFunction(string componentType);
	template <typename type>
	static Component* newComponent(ComponentData componentData);
};

template <typename type>
Component* ComponentFactory::newComponent(ComponentData componentData){
	return new type(componentData);
}