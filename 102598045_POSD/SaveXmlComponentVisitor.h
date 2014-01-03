#pragma once

#include <string>
#include "ComponentVisitor.h"
#include <gtest/gtest_prod.h>

using namespace std;

class SaveXmlComponentVisitor : public ComponentVisitor{
    friend class SaveXmlComponentVisitorTest;
    FRIEND_TEST(SaveXmlComponentVisitorTest,testVisitAttribute);
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
    static const string XmlStart;
    static const string ERDiagramStart,ERDiagramEnd;
    static const string AttributeStart,AttributeEnd;
    static const string EntityStart,EntityEnd;
    static const string RelationShipStart,RelationShipEnd;
    static const string ConnectorStart,ConnectorEnd;
    static const string IdStart,IdEnd;
    static const string TextStart,TextEnd;
    static const string PositionXStart,PositionXEnd;
    static const string PositionYStart,PositionYEnd;
    static const string PrimaryKeyStart,PrimaryKeyEnd;
    static const string SourceStart,SourceEnd;
    static const string TargetStart,TargetEnd;
};