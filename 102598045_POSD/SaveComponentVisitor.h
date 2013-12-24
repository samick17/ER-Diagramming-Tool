#pragma once

#include "ComponentVisitor.h"
#include "Document.h"
#include "HashMap.h"

class Component;

class SaveComponentVisitor : public ComponentVisitor{
public:
    SaveComponentVisitor();
    ~SaveComponentVisitor();

    const vector<string> getResult();
protected:
    void doVisit(Attribute* attribute);
    void doVisit(Entity* entity);
    void doVisit(RelationShip* relationShip);
    void doVisit(Connector* connector);
private:
    void visitComponent(Component* component);
    vector<string> componentInfoVector;
    vector<string> connectionInfoVector;
    vector<string> primaryKeyInfoVector;
};