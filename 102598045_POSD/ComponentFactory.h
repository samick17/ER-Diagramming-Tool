#pragma once

#include "Component.h"
#include "HashMap.h"
#include "ComponentType.h"

typedef Component* (*NewComponentFunction)(ComponentData);

class ComponentFactory{
	friend class ComponentFactoryTest;
	FRIEND_TEST(ComponentFactoryTest,testCreateComponent);
	FRIEND_TEST(ComponentFactoryTest,testFindNewComponentFunction);
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest,testCommandManager);
public:
	ComponentFactory();
	~ComponentFactory();

	Component* createComponent(string componentType);
	void resetFactory();
private:
	static int count;
	HashMap<string,NewComponentFunction> newComponentMap;	
	NewComponentFunction findNewComponentFunction(string componentType);
	template <typename Type>
	static Component* newComponent(ComponentData componentData);
};

template <typename Type>
Component* ComponentFactory::newComponent(ComponentData componentData){
	return new Type(componentData);
}