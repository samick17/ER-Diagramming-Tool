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

    Component* createComponent(string componentType,string name = StringSymbol::Empty);
    void resetFactory();
private:
    static int count;
    HashMap<string,NewComponentFunction> newComponentMap;
    NewComponentFunction findNewComponentFunction(string componentType);
    template <typename Type>
    static Component* newComponent(string componentID,string name);
};

template <typename Type>
Component* ComponentFactory::newComponent(string componentID,string name){
    return new Type(componentID,name);
}