#pragma once

#include "Component.h"
#include "Node.h"
#include "AttributeType.h"
#include "StringSymbol.h"

class Attribute : public Node{
public:
	Attribute(string componentID,string componentName = StringSymbol::Empty);
    ~Attribute();

    int canConnectTo(Component* target);
    bool hasSizeToConnect();

    bool isPrimaryKey();
    void setAsPrimaryKey();

private:
    int attributeType;
};