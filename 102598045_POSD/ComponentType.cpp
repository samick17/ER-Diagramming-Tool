#include "ComponentType.h"
#include "StringSymbol.h"
#include <unordered_map>

string ComponentType::getClassName(string type){
    unordered_map<string,string> typeClassNameMap;
    typeClassNameMap.insert(pair<string,string>(TypeAttribute,TypeAttributeName));
    typeClassNameMap.insert(pair<string,string>(TypeEntity,TypeEntityName));
    typeClassNameMap.insert(pair<string,string>(TypeRelationShip,TypeRelationShipName));
    typeClassNameMap.insert(pair<string,string>(TypeConnector,TypeConnectorName));

    for each(auto iterator in typeClassNameMap)
        if(iterator.first == type)
            return iterator.second;

    return StringSymbol::Empty;
}

const string ComponentType::TypeComponent = "Component";
const string ComponentType::TypeNode = "Node";
const string ComponentType::TypeAttribute = "A";
const string ComponentType::TypeEntity = "E";
const string ComponentType::TypeRelationShip = "R";
const string ComponentType::TypeConnector = "C";
const string ComponentType::TypeAttributeName = "Attribute";
const string ComponentType::TypeEntityName = "Entity";
const string ComponentType::TypeRelationShipName = "RelationShip";
const string ComponentType::TypeConnectorName = "Connector";