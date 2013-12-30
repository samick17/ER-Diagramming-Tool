#include "SaveComponentVisitorTest.h"
#include "Attribute.h"
#include "Connector.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Node.h"

void SaveComponentVisitorTest::SetUp(){
}

void SaveComponentVisitorTest::TearDown(){
}

void SaveComponentVisitorTest::connectWithEachOther(Node* sourceNode,Node* targetNode,Connector* connector){
    sourceNode->connectTo(connector);
    targetNode->connectTo(connector);
    connector->connectTo(sourceNode);
    connector->connectTo(targetNode);
}

TEST_F(SaveComponentVisitorTest,testGetResult){
    HashMap<string,string> reorderIDMap;
    HashMap<string,Component*> componentMap;

    Entity engineer("7","Engineer");
    Attribute id("12","ID");
    Attribute name("3","Name");
    RelationShip has("6","Has");
    Entity pc("2","PC");
    Attribute purchase_date("10","Purchase_Date");
    Attribute device_id("5","Device_ID");
    Connector connectorEngineerID("13");
    this->connectWithEachOther(&engineer,&id,&connectorEngineerID);
    Connector connectorEngineerName("16");
    this->connectWithEachOther(&engineer,&name,&connectorEngineerName);
    Connector connectorEngineerHas("18","1");
    this->connectWithEachOther(&engineer,&has,&connectorEngineerHas);
    Connector connectorPC_PurchasDate("14");
    this->connectWithEachOther(&pc,&purchase_date,&connectorPC_PurchasDate);
    Connector connectorPC_Device_ID("21");
    this->connectWithEachOther(&pc,&device_id,&connectorPC_Device_ID);
    Connector connectorPCHas("24","1");
    this->connectWithEachOther(&pc,&has,&connectorPCHas);

    id.setAsPrimaryKey();
    device_id.setAsPrimaryKey();

    componentMap.put(engineer.getID(),&engineer);
    componentMap.put(id.getID(),&id);
    componentMap.put(name.getID(),&name);
    componentMap.put(has.getID(),&has);
    componentMap.put(pc.getID(),&pc);
    componentMap.put(purchase_date.getID(),&purchase_date);
    componentMap.put(device_id.getID(),&device_id);

    componentMap.put(connectorEngineerID.getID(),&connectorEngineerID);
    componentMap.put(connectorEngineerName.getID(),&connectorEngineerName);
    componentMap.put(connectorEngineerHas.getID(),&connectorEngineerHas);
    componentMap.put(connectorPC_PurchasDate.getID(),&connectorPC_PurchasDate);
    componentMap.put(connectorPC_Device_ID.getID(),&connectorPC_Device_ID);
    componentMap.put(connectorPCHas.getID(),&connectorPCHas);

    reorderIDMap.put("7","0");
    reorderIDMap.put("12","1");
    reorderIDMap.put("3","2");
    reorderIDMap.put("6","3");
    reorderIDMap.put("2","4");
    reorderIDMap.put("10","5");
    reorderIDMap.put("5","6");
    reorderIDMap.put("13","7");
    reorderIDMap.put("16","8");
    reorderIDMap.put("18","19");
    reorderIDMap.put("14","11");
    reorderIDMap.put("21","12");
    reorderIDMap.put("24","13");

    SaveComponentVisitor saveComponentVisitor(reorderIDMap);
    for each(Component* component in componentMap){
        component->accept(&saveComponentVisitor);
    }

    ASSERT_EQ(13,saveComponentVisitor.componentInfoVector.size());
    ASSERT_EQ(6,saveComponentVisitor.connectionInfoVector.size());
    ASSERT_EQ(2,saveComponentVisitor.primaryKeyInfoVector.size());

    vector<string> result = saveComponentVisitor.getResult();
    ASSERT_EQ(23,result.size());
    string resultToString;
    for each(string str in result){
        resultToString.append(str);
        resultToString.append("\n");
    }//E A A R E A A C C C C C C
    string expected = "E, Engineer\nA, ID\nA, Name\nR, Has\nE, PC\nA, Purchase_Date\nA, Device_ID\nC\nC\nC, 1\nC\nC\nC, 1\n\n7 0,1\n8 0,2\n19 0,3\n11 4,5\n12 4,6\n13 4,3\n\n0 1\n4 6\n";
    ASSERT_EQ(expected,resultToString);
}

TEST_F(SaveComponentVisitorTest,testVisitEntity){
    Entity entity("10","Engineer");
    entity.setPosition(Point(-1000,0));
    Attribute id("3","ID");
    Attribute name("7","name");
    Connector connectorEntityID("8");
    this->connectWithEachOther(&entity,&name,&connectorEntityID);

    Connector connectorEntityName("12");
    this->connectWithEachOther(&entity,&id,&connectorEntityName);

    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("10","0");
    reorderIDMap.put("3","1");
    reorderIDMap.put("7","2");
    reorderIDMap.put("8","3");
    reorderIDMap.put("12","4");
    SaveComponentVisitor saveComponentVisitor(reorderIDMap);
    saveComponentVisitor.visit(&entity);
    ASSERT_EQ(entity.getType()+", Engineer",saveComponentVisitor.componentInfoVector[0]);
    ASSERT_EQ("-1000 0",saveComponentVisitor.positionInfoVector[0]);
    ASSERT_EQ(true,saveComponentVisitor.primaryKeyInfoVector.empty());

    id.setAsPrimaryKey();
    saveComponentVisitor.visit(&entity);
    ASSERT_EQ(entity.getType()+", Engineer",saveComponentVisitor.componentInfoVector[1]);
    ASSERT_EQ("-1000 0",saveComponentVisitor.positionInfoVector[1]);
    ASSERT_EQ("0 1",saveComponentVisitor.primaryKeyInfoVector[0]);

    name.setAsPrimaryKey();
    saveComponentVisitor.visit(&entity);
    ASSERT_EQ(entity.getType()+", Engineer",saveComponentVisitor.componentInfoVector[2]);
    ASSERT_EQ("-1000 0",saveComponentVisitor.positionInfoVector[2]);
    ASSERT_EQ("0 2,1",saveComponentVisitor.primaryKeyInfoVector[1]);
}

TEST_F(SaveComponentVisitorTest,testVisitConnector){
    Connector connector("3","1");
    Entity entity("1","Engineer");
    Attribute name("2","Name");
    this->connectWithEachOther(&entity,&name,&connector);

    HashMap<string,string> reorderIDMap;
    reorderIDMap.put("3","5");
    reorderIDMap.put("1","0");
    reorderIDMap.put("2","4");
    SaveComponentVisitor saveComponentVisitor(reorderIDMap);

    saveComponentVisitor.visit(&connector);
    ASSERT_EQ("5 0,4",saveComponentVisitor.connectionInfoVector[0]);
}

TEST_F(SaveComponentVisitorTest,testVisitComponent){
    HashMap<string,string> reorderIDMap;
    SaveComponentVisitor saveComponentVisitor(reorderIDMap);

    reorderIDMap.put("3","1");
    Attribute attributeWithName("3","TestAttribute");
    saveComponentVisitor.visitComponent(&attributeWithName);
    ASSERT_EQ(attributeWithName.getType()+", TestAttribute",saveComponentVisitor.componentInfoVector[0]);

    reorderIDMap.put("4","3");
    Attribute attributeNoName("4",StringSymbol::Empty);
    saveComponentVisitor.visitComponent(&attributeNoName);
    ASSERT_EQ(attributeNoName.getType(),saveComponentVisitor.componentInfoVector[1]);
}

TEST_F(SaveComponentVisitorTest,testRecordPosition){
    HashMap<string,string> reorderIDMap;
    SaveComponentVisitor saveComponentVisitor(reorderIDMap);

    Attribute attribute("0","Name");
    attribute.setPosition(Point(-1,5.5));
    saveComponentVisitor.recordPosition(&attribute);
    ASSERT_EQ("-1 5.5",saveComponentVisitor.positionInfoVector[0]);
}