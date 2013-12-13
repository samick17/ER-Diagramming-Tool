#pragma once

#include <string>
#include "HashMap.h"
#include "ComponentData.h"
#include "NodeConnectionType.h"
#include <gtest/gtest_prod.h>

using namespace std;

class Component{
    friend class ERModelTest;
    FRIEND_TEST(ERModelTest,addConnection);
    friend class ConnectorTest;
    FRIEND_TEST(ConnectorTest,testBreakAllConnections);
public:
    Component();
    virtual ~Component();

    string getID();
    string getType();
    string getClassName();
    string getName();
    void setName(string name);
    Rect getRect();
    virtual void setPosition(Point position) = 0;
    virtual void setCenterPosition(Point position) = 0;
    void setSize(Size size);
    ComponentData* getComponentData();
    HashMap<string,Component*> getAllConnections();

    template<typename Type>
    bool isTypeOf();

    void connectTo(Component* target);
    void disconnectTo(Component* target);
    virtual void breakAllConnections() = 0;
    virtual int canConnectTo(Component* target) = 0;
    virtual bool hasSizeToConnect();
    bool hasConnectedTo(Component* target);
protected:
    ComponentData* componentData;
private:
    HashMap<string,Component*> connectionMap;
};

template<typename Type>
bool Component::isTypeOf(){
    return typeid(*this).name() == typeid(Type).name();
}