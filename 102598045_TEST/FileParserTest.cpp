#include "FileParserTest.h"
#include "StringSymbol.h"

void FileParserTest::SetUp(){
	this->fileParser.erModel = &erModel;
	this->document = new Document("TestDoc");
	document->wirteLine("E, Engineer");
	document->wirteLine("A, Emp_ID");
	document->wirteLine("R, Has");
	document->wirteLine("A, Name");
	document->wirteLine("E, PC");
	document->wirteLine("A, PC_ID");
	document->wirteLine("A, Purchase_Date");
	document->wirteLine("C");
	document->wirteLine("C");
	document->wirteLine("C");
	document->wirteLine("C");
	document->wirteLine("C, 1");
	document->wirteLine("C, 1");
	document->wirteLine("A, Department");
	document->wirteLine("C");
	document->wirteLine("");
	document->wirteLine("7 0,1");
	document->wirteLine("8 0,3");
	document->wirteLine("9 4,5");
	document->wirteLine("10 4,6");
	document->wirteLine("11 0,2");
	document->wirteLine("12 2,4");
	document->wirteLine("14 0,13");
	document->wirteLine("");
	document->wirteLine("0 1,3");
	document->wirteLine("4 5");
	document->wirteLine("");
	ASSERT_EQ(true,this->fileParser.componentDataQueue.empty());
	ASSERT_EQ(true,this->fileParser.connectionDataQueue.empty());
}

void FileParserTest::TearDown(){
	delete this->document;
}

TEST_F(FileParserTest,testLoadAllComponentsFromDoc){	
	ASSERT_EQ(true,this->fileParser.componentDataQueue.empty());
	this->fileParser.loadAllComponentsFromDoc(*this->document);
	ASSERT_EQ(15,this->fileParser.componentDataQueue.size());
}

TEST_F(FileParserTest,testLoadAllConnectorsFromDoc){
}

TEST_F(FileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc){
}

TEST_F(FileParserTest,testAddAllComponentToERModel){
}

TEST_F(FileParserTest,testAddConnector){
}

TEST_F(FileParserTest,testIsQueueArriveConnectionDataID){
}