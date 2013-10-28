#pragma once

#include <stack>
#include "EmptyCollectionException.h"
#include "CollectionType.h"

class StackUtil{
public:
    template<typename Type>
    static void deleteAllElementsInStack(stack<Type*>& typesStack);

    template<typename Type>
    static Type* pop(stack<Type*>& typeStack);
};
//delete all elements in stack
template<typename Type>
static void StackUtil::deleteAllElementsInStack(stack<Type*>& typesStack){
    while(!typesStack.empty()){            
        Type* typePointer = typesStack.top();
        typesStack.pop();
        if(typePointer != NULL)
            delete typePointer;        
    }
}
//pop and return object
template<typename Type>
static Type* StackUtil::pop(stack<Type*>& typeStack){
    if(typeStack.empty())
        throw EmptyCollectionException(CollectionType::TypeStack);
    Type* typePointer = typeStack.top();
    typeStack.pop();
    return typePointer;
}