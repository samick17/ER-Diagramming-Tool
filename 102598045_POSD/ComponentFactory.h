#pragma once

#include "Component.h"
#include "HashMap.h"
#include "ComponentType.h"
#include "StringSymbol.h"

typedef Component* (*NewComponentFunction)(string componentID,string name);

class ComponentFactory{
    friend class ComponentFactoryTest;
    FRIEND_TEST(ComponentFactoryTest,testCreateComponent);
    FRIEND_TEST(ComponentFactoryTest,testFindNewComponentFunction);
    FRIEND_TEST(ComponentFactoryTest,testResetFactory);
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
public:
    ComponentFactory();
    ~ComponentFactory();

    Component* createComponent(string componentType,string componentID,string name = StringSymbol::Empty);
private:
    template <typename Type>
    static Component* newComponent(string componentID,string name);

    NewComponentFunction findNewComponentFunction(string componentType);
    HashMap<string,NewComponentFunction> newComponentMap;
};

template <typename Type>
Component* ComponentFactory::newComponent(string componentID,string name){
    return new Type(componentID,name);
}