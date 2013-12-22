#pragma once

#include "Component.h"
#include "StringSymbol.h"

class Connector : public Component{
    friend class ConnectorTest;
public:
    Connector(string componentID,string componentName = StringSymbol::Empty);
    ~Connector();

    void setPosition(Point position);
    void setCenterPosition(Point position);
    void updateRect();

    void breakAllConnections();
    int canConnectTo(Component* target);
    bool hasSizeToConnect();

    Component* getFirstConnectedNode();
    Component* getSecondConnectedNode();
    bool isNodesConnection(Component* firstNode,Component* secondNode);
    bool isCardinalityConnector();

    void accept(ComponentVisitor* visitor);

    Component* clone() const;
};