#pragma once

#include <vector>
#include <set>

class VectorUtil{
public:
	template<typename type>
	static set<type> convertVectorToSet(vector<type> typeVector);
};
//insert all elements from vector to set
template<typename type>
static set<type> VectorUtil::convertVectorToSet(vector<type> typeVector){
	set<type> typeSet;
	for each(type typeObject in typeVector){
		typeSet.insert(typeObject);
	}
	return typeSet;
}