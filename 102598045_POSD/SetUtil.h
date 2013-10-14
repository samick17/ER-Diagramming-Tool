#pragma once

#include <set>

class SetUtil{
public:
	template<typename type>
	static void deleteAllElementsInSet(set<type*>& typeSet);
};
//delete all elements in set and clear this set
template<typename type>
static void SetUtil::deleteAllElementsInSet(set<type*>& typeSet){
	for each(type* typePointer in typeSet){
		if(typePointer != NULL){
			delete typePointer;
			typePointer = NULL;
		}
	}
	typeSet.clear();
}