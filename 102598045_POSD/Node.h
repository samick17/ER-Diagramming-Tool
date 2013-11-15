#pragma once

#include "Component.h"

class Node : public Component{
public:
    Node(ComponentData componentData);
    ~Node();

    string getType();
    void setPosition(Point position);
    void setCenterPosition(Point position);

    void breakAllConnections();
    int canConnectTo(Component* target);
    bool hasSizeToConnect();
private:
    void updateConnectorsPosition();
};