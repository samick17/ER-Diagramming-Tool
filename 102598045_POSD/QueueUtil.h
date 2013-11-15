#pragma once

#include <queue>
#include "EmptyCollectionException.h"
#include "CollectionType.h"

class QueueUtil{
public:
    //dequeue
    template<typename Type>
    static Type dequeue(queue<Type>& typeQueue);
};
    //dequeue
template<typename Type>
static Type QueueUtil::dequeue(queue<Type>& typeQueue){
    if(typeQueue.empty())
        throw EmptyCollectionException(CollectionType::TypeQueue);
    Type typeObject = typeQueue.front();
    typeQueue.pop();
    return typeObject;
}