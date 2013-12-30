#pragma once

#include "ComponentVisitor.h"
#include "Document.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h>

class Component;
class Node;

class SaveComponentVisitor : public ComponentVisitor{
    friend class SaveComponentVisitorTest;
    FRIEND_TEST(SaveComponentVisitorTest,testVisitComponent);
    FRIEND_TEST(SaveComponentVisitorTest,testRecordPosition);
    FRIEND_TEST(SaveComponentVisitorTest,testVisitConnector);
    FRIEND_TEST(SaveComponentVisitorTest,testVisitEntity);
    FRIEND_TEST(SaveComponentVisitorTest,testGetResult);
public:
    SaveComponentVisitor(HashMap<string,string> reorderedIDMap);
    ~SaveComponentVisitor();

    const vector<string> getResult();
    const vector<string> getPositionInfoVector();

    void visit(Attribute* attribute);
    void visit(Entity* entity);
    void visit(RelationShip* relationShip);
    void visit(Connector* connector);
private:
    void visitComponent(Component* component);
    void recordPosition(Node* node);
    vector<string> componentInfoVector;
    vector<string> connectionInfoVector;
    vector<string> primaryKeyInfoVector;
    vector<string> positionInfoVector;
};