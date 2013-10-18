#pragma once

#include <stack>

class StackUtil{
public:
	template<typename type>
	static void deleteAllElementsInStack(stack<type*>& typesStack);

	template<typename type>
	static type* pop(stack<type*>& typeStack,string errmessage);
};
//delete all elements in stack
template<typename type>
static void StackUtil::deleteAllElementsInStack(stack<type*>& typesStack){
	while(!typesStack.empty()){			
		type* typePointer = typesStack.top();
		typesStack.pop();
		if(typePointer != NULL){
			delete typePointer;
		}
	}
}
//pop and return object
template<typename type>
static type* StackUtil::pop(stack<type*>& typeStack,string errmessage){
	if(typeStack.empty())
		return NULL;
	type* typePointer = typeStack.top();
	typeStack.pop();
	return typePointer;
}