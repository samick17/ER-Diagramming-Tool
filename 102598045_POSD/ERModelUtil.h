#pragma once

#include <set>
#include <vector>
#include "Component.h"
#include "StringUtil.h"
#include "TableManager.h"
#include "RelationShip.h"
#include "EmptyCollectionException.h"

class ERModelUtil{
public:
	//template cant be put in cpp file
	template<typename type> 
	static set<type*> convertComponentSetToTypeSet(set<Component*> componentSet);

	template<typename type> 
	static vector<type*> convertComponentVectorToTypeVector(vector<Component*> componentVector);

	template <typename type>
	static vector<type*> convertComponentSetToOrderedVector(vector<string> orderedVector,set<type*> typeSet);

	static unordered_map<string,Table*> convertToTableMap(TableManager& tableManager,set<RelationShip*> relationShipSet);
private:
	static set<RelationShip*> getOneToOneRelationShips(set<RelationShip*> relationShipSet);
	static void appendOneToOneTable(TableManager& tableManager,set<RelationShip*> relationShipSet);	
};
//convert component set to concrete type set
template<typename type> 
static set<type*> ERModelUtil::convertComponentSetToTypeSet(set<Component*> componentSet){
	set<type*> typeSet;	
	for each (Component* component in componentSet){	
		if(typeid(*component).name() == typeid(type).name()){
			typeSet.insert(static_cast<type*>(component));
		}
	}
	return typeSet;
}
//convert component vector to concrete type vector
template<typename type> 
static vector<type*> ERModelUtil::convertComponentVectorToTypeVector(vector<Component*> componentVector){
	vector<type*> typeVector;	
	for each (Component* component in componentVector){	
		if(typeid(*component).name() == typeid(type).name()){
			typeVector.push_back(static_cast<type*>(component));
		}
	}
	return typeVector;
}
//convert ComponentSet to OrderdVector, because 'set' will auto sort....
template <typename type>
static vector<type*> ERModelUtil::convertComponentSetToOrderedVector(vector<string> orderedVector,set<type*> typeSet){
	unordered_map<string,type*> typeMap;
	for each(type* typePointer in typeSet){
		Component* component = (static_cast<Component*>(typePointer));
		typeMap.insert(pair<string,type*>(component->getID(),typePointer));
	}

	vector<type*> typeVector;
	for each(string id in orderedVector){
		unordered_map<string,type*>::iterator typeIterator;
		if((typeIterator = typeMap.find(id)) != typeMap.end())
			typeVector.push_back(typeIterator->second);
	}
	return typeVector;
}