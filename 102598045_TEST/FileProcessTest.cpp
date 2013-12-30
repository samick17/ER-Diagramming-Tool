#include "FileProcessTest.h"
#include "FileProcess.h"
#include "Exception.h"

void FileProcessTest::SetUp(){
}

void FileProcessTest::TearDown(){
}

TEST_F(FileProcessTest,testExtractFileInfo){
    FileProcess fileProcess = FileProcess("C:\ERD\test.erd");

    ASSERT_EQ("C:\ERD\test",fileProcess.fileName);
    ASSERT_EQ(".erd",fileProcess.fileExtension);

    fileProcess.extractFileInfo("C:\ERD\TestFile\test.1.erd");
    ASSERT_EQ("C:\ERD\TestFile\test.1",fileProcess.fileName);
    ASSERT_EQ(".erd",fileProcess.fileExtension);

    ASSERT_THROW(fileProcess.extractFileInfo("abcd"),Exception);
}