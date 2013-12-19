#pragma once

#include "HashMap.h"

class HashMapUtil{
public:
    template<typename Key,typename Value>
    static void deleteAll(HashMap<Key,Value*>& map);
};
//delete all elements in map
template<typename Key,typename Value>
static void HashMapUtil::deleteAll(HashMap<Key,Value*>& map){
    for each(Value* value in map)
        delete value;
    map.clear();
}