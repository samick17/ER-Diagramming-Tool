#include "ConnectorDataTest.h"
#include "ConnectorData.h"

void ConnectorDataTest::SetUp(){
}

void ConnectorDataTest::TearDown(){
}

TEST_F(ConnectorDataTest,testSetPointPair){
	ConnectorData connectorData = ConnectorData(ComponentData("test","0"));
	Point sourcePoint = Point(-100,-150);
	Point targetPoint = Point(203,300);
    pair<Point,Point> pointPair = pair<Point,Point>(sourcePoint,targetPoint);
    connectorData.setPointPair(pointPair);
	
	ASSERT_EQ(pointPair.first,connectorData.getSourcePoint());
	ASSERT_EQ(pointPair.second,connectorData.getTargetPoint());

	ASSERT_EQ(min(sourcePoint.getX(),targetPoint.getX()),connectorData.getRect().getPosition().getX());
	ASSERT_EQ(min(sourcePoint.getY(),targetPoint.getY()),connectorData.getRect().getPosition().getY());
	ASSERT_EQ(abs(sourcePoint.getX()-targetPoint.getX()),connectorData.getRect().getWidth());
	ASSERT_EQ(abs(sourcePoint.getY()-targetPoint.getY()),connectorData.getRect().getHeight());
}