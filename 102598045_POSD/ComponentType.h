#pragma once

#include <string>

using namespace std;

class ComponentType{
public:
    static string getClassName(string type);

    static const string TypeComponent;
    static const string TypeNode;
    static const string TypeAttribute;
    static const string TypeEntity;
    static const string TypeRelationShip;
    static const string TypeConnector;
    static const string TypeAttributeName;
    static const string TypeEntityName;
    static const string TypeRelationShipName;
    static const string TypeConnectorName;
};