#include "DocumentTest.h"
#include "DirectoryUtil.h"
#include "StringSymbol.h"
#include "FileNotFoundException.h"

void DocumentTest::SetUp(){
	string filepath = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/testDocument.txt";
	this->document = new Document(filepath);
}

void DocumentTest::TearDown(){
	string filepath = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/testDocument.txt";
	remove(filepath.c_str());
	delete this->document;
}

TEST_F(DocumentTest,testDocument){	
	ASSERT_EQ(0,this->document->rwBuffer.size());
	//test write
	this->document->wirteLine("testLine1");
	this->document->wirteLine("testXXXXXXX");
	this->document->wirteLine("Hello~~");
	this->document->wirteLine("_)*(@&*^@$");
	ASSERT_EQ(4,this->document->rwBuffer.size());
	//test read
	ASSERT_EQ("testLine1"+StringSymbol::NextLine,this->document->readLine());
	ASSERT_EQ("testXXXXXXX"+StringSymbol::NextLine,this->document->readLine());
	ASSERT_EQ("Hello~~"+StringSymbol::NextLine,this->document->readLine());
	ASSERT_EQ("_)*(@&*^@$"+StringSymbol::NextLine,this->document->readLine());
	//test save	
	this->document->wirteLine("testLine1");
	this->document->wirteLine("testXXXXXXX");
	this->document->wirteLine("Hello~~");
	this->document->wirteLine("_)*(@&*^@$");
	this->document->saveFile();
	//reconstruct
	delete this->document;
	string filepath = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/testDocument.txt";
	this->document = new Document(filepath);
	//test open	
	this->document->openFile();
	ASSERT_EQ("testLine1",this->document->readLine());
	ASSERT_EQ("testXXXXXXX",this->document->readLine());
	ASSERT_EQ("Hello~~",this->document->readLine());
	ASSERT_EQ("_)*(@&*^@$",this->document->readLine());

	//test open not existed file
	filepath = DirectoryUtil::getCurrentWorkingDirectory()+"/Debug/*(&#(*!S!).*!*(!W";
	this->document->filePath = filepath;
	ASSERT_THROW(this->document->openFile(),FileNotFoundException);
}