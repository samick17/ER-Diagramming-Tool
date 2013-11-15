#pragma once

#include "Component.h"
#include <queue>

class Connector : public Component{
    friend class ConnectorTest;
public:
    Connector(ComponentData componentData);
    ~Connector();
    
    string getType();
    void setPosition(Point position);
    void setCenterPosition(Point position);
    void updateRect();

    void breakAllConnections();
    int canConnectTo(Component* target);
    bool hasSizeToConnect();

    Component* getFirstConnectedNode();
    Component* getSecondConnectedNode();
    bool isNodesConnection(Component* firstNode,Component* secondNode);
};