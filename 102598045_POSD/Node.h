#pragma once

#include "Component.h"

class Node : public Component{
public:
    Node(string type,string componentID,string componentName);
    ~Node();

    void setName(string name);
    void setPosition(Point position);
    void setCenterPosition(Point position);

    void breakAllConnections();
    int canConnectTo(Component* target);
private:
    void updateConnectorsPosition();
};