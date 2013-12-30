#include "SaveXmlComponentVisitorTest.h"
#include "Attribute.h"

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
    SaveXmlComponentVisitor saveXmlComponentVisitor(reorderIDMap);

    saveXmlComponentVisitor.visit(&attribute);
    ASSERT_EQ("    <Attribute>",saveXmlComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("        <Id>3</Id>",saveXmlComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("        <Text>TestAttributeName</Text>",saveXmlComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("        <PositionX>-0.5</PositionX>",saveXmlComponentVisitor.componentInfoVector[3]);
    ASSERT_EQ("        <PositionY>0.2</PositionY>",saveXmlComponentVisitor.componentInfoVector[4]);
    ASSERT_EQ("    </Attribute>",saveXmlComponentVisitor.componentInfoVector[5]);
}

TEST_F(SaveXmlComponentVisitorTest,testVisitEntity){
}

TEST_F(SaveXmlComponentVisitorTest,testVisitRelationShip){
}

TEST_F(SaveXmlComponentVisitorTest,testVisitConnector){
}