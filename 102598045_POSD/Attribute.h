#pragma once

#include "Component.h"
#include "Node.h"
#include "AttributeType.h"

class Attribute : public Node{
public:        
    Attribute(ComponentData componentData);
    ~Attribute();

    string getType();
    
    int canConnectTo(Component* target);
    bool hasSizeToConnect();

    bool isPrimaryKey();
    void setAsPrimaryKey();
private:
    int attributeType;
};