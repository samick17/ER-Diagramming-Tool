#pragma once

#include "Component.h"

class Node : public Component{
public:
    Node(ComponentData componentData);
    ~Node();

    string getType();

    void breakAllConnections();
    int canConnectTo(Component* target);
    bool hasSizeToConnect();
};