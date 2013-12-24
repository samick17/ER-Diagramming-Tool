#pragma once

#include "ComponentVisitor.h"

class SaveXmlComponentVisitor : public ComponentVisitor{
public:
    SaveXmlComponentVisitor(HashMap<string,string> reorderedIDMap);
    ~SaveXmlComponentVisitor();

    const vector<string> getResult();

    void visit(Attribute* attribute);
    void visit(Entity* entity);
    void visit(RelationShip* relationShip);
    void visit(Connector* connector);
private:
    vector<string> componentInfoVector;
};