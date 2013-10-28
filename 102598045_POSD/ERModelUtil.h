#pragma once

#include <vector>
#include "HashMap.h"
#include "Component.h"

class ERModelUtil{
public:
    //template cant be put in cpp file
    template<typename Type> 
    static HashMap<string,Type*> convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap);    
};
//convert component hashmap to concrete type hashmap
template<typename Type> 
static HashMap<string,Type*> ERModelUtil::convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap){
    HashMap<string,Type*> typeHashMap;
    for each(Component* component in componentHashMap)
        if(typeid(*component).name() == typeid(Type).name())
            typeHashMap.put(component->getID(),static_cast<Type*>(component));
    return typeHashMap;
}