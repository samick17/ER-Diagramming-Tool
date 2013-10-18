#pragma once

#include <set>
#include <vector>
#include "HashMap.h"
#include "Component.h"
#include "StringUtil.h"
#include "TableManager.h"
#include "RelationShip.h"
#include "EmptyCollectionException.h"

class ERModelUtil{
public:
	//template cant be put in cpp file
	template<typename type> 
	static HashMap<string,type*> convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap);
	
	template<typename type> 
	static vector<type*> convertComponentVectorToTypeVector(vector<Component*> componentVector);

	static HashMap<string,Table*> convertToTableMap(TableManager& tableManager,HashMap<string,RelationShip*> relationShipSet);
private:
	static HashMap<string,RelationShip*> getOneToOneRelationShips(HashMap<string,RelationShip*> relationShipSet);
	static void appendOneToOneTable(TableManager& tableManager,HashMap<string,RelationShip*> relationShipSet);	
	static void insertAllForeignKeyToTable(TableManager& tableManager,RelationShip* relationShip);
};
//convert component hashmap to concrete type hashmap
template<typename type> 
static HashMap<string,type*> ERModelUtil::convertComponentHashMapToTypeHashMap(HashMap<string,Component*> componentHashMap){
	HashMap<string,type*> typeHashMap;
	for each (Component* component in componentHashMap){	
		if(typeid(*component).name() == typeid(type).name()){
			typeHashMap.put(component->getID(),static_cast<type*>(component));
		}
	}
	return typeHashMap;
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