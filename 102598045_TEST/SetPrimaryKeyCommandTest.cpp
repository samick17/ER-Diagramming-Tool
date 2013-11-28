#include "SetPrimaryKeyCommandTest.h"
#include "SetPrimaryKeyCommand.h"
#include "Attribute.h"

void SetPrimaryKeyCommandTest::SetUp(){
}

void SetPrimaryKeyCommandTest::TearDown(){
}

TEST_F(SetPrimaryKeyCommandTest,testExecute){
    Attribute* attribute = new Attribute("0");
    attribute->setAsPrimaryKey();
    SetPrimaryKeyCommand setPrimaryKeyCommand = SetPrimaryKeyCommand(attribute);

    setPrimaryKeyCommand.execute();
    ASSERT_EQ(false,attribute->isPrimaryKey());
    //test execute again
    setPrimaryKeyCommand.execute();
    ASSERT_EQ(false,attribute->isPrimaryKey());

    ////////////////////////////////////////////////
    attribute->setAsDefaultKey();
    setPrimaryKeyCommand = SetPrimaryKeyCommand(attribute);

    setPrimaryKeyCommand.execute();
    ASSERT_EQ(true,attribute->isPrimaryKey());
    //test execute again
    setPrimaryKeyCommand.execute();
    ASSERT_EQ(true,attribute->isPrimaryKey());
    delete attribute;
}

TEST_F(SetPrimaryKeyCommandTest,testUnexecute){
    Attribute* attribute = new Attribute("0");
    attribute->setAsPrimaryKey();
    SetPrimaryKeyCommand setPrimaryKeyCommand = SetPrimaryKeyCommand(attribute);
    setPrimaryKeyCommand.executionFlag = true;

    setPrimaryKeyCommand.unExecute();
    ASSERT_EQ(true,attribute->isPrimaryKey());
    //test execute again
    setPrimaryKeyCommand.unExecute();
    ASSERT_EQ(true,attribute->isPrimaryKey());
    ////////////////////////////////////////////////
    attribute->setAsDefaultKey();
    setPrimaryKeyCommand = SetPrimaryKeyCommand(attribute);
    setPrimaryKeyCommand.executionFlag = true;

    setPrimaryKeyCommand.unExecute();
    ASSERT_EQ(false,attribute->isPrimaryKey());
    //test execute again
    setPrimaryKeyCommand.unExecute();
    ASSERT_EQ(false,attribute->isPrimaryKey());
    delete attribute;
}