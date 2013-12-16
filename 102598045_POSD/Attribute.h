#pragma once

#include "Component.h"
#include "Node.h"

class Attribute : public Node{
    friend class AttributeTest;
    FRIEND_TEST(AttributeTest,testSetAsPrimaryKey);
    FRIEND_TEST(AttributeTest,testSetAsDefaultKey);
public:
    Attribute(string componentID,string componentName = StringSymbol::Empty);
    ~Attribute();

    int canConnectTo(Component* target);
    bool hasSizeToConnect();
    bool isPrimaryKey();
    void setAsPrimaryKey();
    void setAsDefaultKey();

    Component* clone();
private:
    int attributeType;
};