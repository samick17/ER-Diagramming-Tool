#pragma once

#include "Component.h"

class Node : public Component{
public:
    Node(string componentID,string type);
    ~Node();

    void setPosition(Point position);
    void setCenterPosition(Point position);

    void breakAllConnections();
    int canConnectTo(Component* target);
    bool hasSizeToConnect();
private:
    void updateConnectorsPosition();
};