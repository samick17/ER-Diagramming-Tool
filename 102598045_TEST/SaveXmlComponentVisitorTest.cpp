#include "SaveXmlComponentVisitorTest.h"
#include "Attribute.h"
#include "Entity.h"
#include "Connector.h"
#include "RelationShip.h"

void SaveXmlComponentVisitorTest::SetUp(){
}

void SaveXmlComponentVisitorTest::TearDown(){
}

TEST_F(SaveXmlComponentVisitorTest,testGetResult){
}

TEST_F(SaveXmlComponentVisitorTest,testVisitAttribute){
    Attribute attribute("3","TestAttributeName");
    attribute.setPosition(Point(-0.5,0.2));
    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("3","0");
    SaveXmlComponentVisitor saveXmlComponentVisitor(reorderIDMap);

    saveXmlComponentVisitor.visit(&attribute);
    ASSERT_EQ("    <Attribute>",saveXmlComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("        <Id>0</Id>",saveXmlComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("        <Text>TestAttributeName</Text>",saveXmlComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("        <PositionX>-0.5</PositionX>",saveXmlComponentVisitor.componentInfoVector[3]);
    ASSERT_EQ("        <PositionY>0.2</PositionY>",saveXmlComponentVisitor.componentInfoVector[4]);
    ASSERT_EQ("    </Attribute>",saveXmlComponentVisitor.componentInfoVector[5]);
}

TEST_F(SaveXmlComponentVisitorTest,testVisitEntity){
    Entity entity("2","TestEntity");
    entity.setPosition(Point(-100,12));
    Attribute attribute("3","TestAttribute");
    Connector connector("7");
    connector.connectTo(&entity);
    connector.connectTo(&attribute);
    entity.connectTo(&connector);
    attribute.connectTo(&connector);
    attribute.setAsPrimaryKey();

    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("2","0");
    reorderIDMap.put("3","1");
    reorderIDMap.put("7","2");
    SaveXmlComponentVisitor saveXmlComponentVisitor(reorderIDMap);

    saveXmlComponentVisitor.visit(&entity);
    ASSERT_EQ("    <Entity>",saveXmlComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("        <Id>0</Id>",saveXmlComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("        <Text>TestEntity</Text>",saveXmlComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("        <PrimaryKey>1</PrimaryKey>",saveXmlComponentVisitor.componentInfoVector[3]);
    ASSERT_EQ("        <PositionX>-100</PositionX>",saveXmlComponentVisitor.componentInfoVector[4]);
    ASSERT_EQ("        <PositionY>12</PositionY>",saveXmlComponentVisitor.componentInfoVector[5]);
    ASSERT_EQ("    </Entity>",saveXmlComponentVisitor.componentInfoVector[6]);
}

TEST_F(SaveXmlComponentVisitorTest,testVisitRelationShip){
    RelationShip relationShip("10","Test  RelationShip");
    relationShip.setPosition(Point(-120,11));

    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("10","0");
    SaveXmlComponentVisitor saveXmlComponentVisitor(reorderIDMap);

    saveXmlComponentVisitor.visit(&relationShip);
    ASSERT_EQ("    <RelationShip>",saveXmlComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("        <Id>0</Id>",saveXmlComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("        <Text>Test  RelationShip</Text>",saveXmlComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("        <PositionX>-120</PositionX>",saveXmlComponentVisitor.componentInfoVector[3]);
    ASSERT_EQ("        <PositionY>11</PositionY>",saveXmlComponentVisitor.componentInfoVector[4]);
    ASSERT_EQ("    </RelationShip>",saveXmlComponentVisitor.componentInfoVector[5]);
}

TEST_F(SaveXmlComponentVisitorTest,testVisitConnector){
    Entity entity("2","TestEntity");
    entity.setPosition(Point(-100,12));
    Attribute attribute("3","TestAttribute");
    Connector connector("7");
    connector.connectTo(&entity);
    connector.connectTo(&attribute);
    entity.connectTo(&connector);
    attribute.connectTo(&connector);

    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("2","0");
    reorderIDMap.put("3","1");
    reorderIDMap.put("7","2");
    SaveXmlComponentVisitor saveXmlComponentVisitor(reorderIDMap);

    saveXmlComponentVisitor.visit(&connector);
    ASSERT_EQ("    <Connector>",saveXmlComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("        <Id>2</Id>",saveXmlComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("        <Text></Text>",saveXmlComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("        <Source>0</Source>",saveXmlComponentVisitor.componentInfoVector[3]);
    ASSERT_EQ("        <Target>1</Target>",saveXmlComponentVisitor.componentInfoVector[4]);
    ASSERT_EQ("    </Connector>",saveXmlComponentVisitor.componentInfoVector[5]);
}