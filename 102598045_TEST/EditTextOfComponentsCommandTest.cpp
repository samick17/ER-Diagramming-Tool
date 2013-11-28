#include "EditTextOfComponentsCommandTest.h"
#include "EditTextOfComponentsCommand.h"
#include "Attribute.h"

void EditTextOfComponentsCommandTest::SetUp(){
}

void EditTextOfComponentsCommandTest::TearDown(){
}

TEST_F(EditTextOfComponentsCommandTest,testExecute){
    Component* attribute = new Attribute("0","testEditAttributeName");
    EditTextOfComponentsCommand editTextOfComponentsCommand = EditTextOfComponentsCommand(attribute,"testAttribute");

    editTextOfComponentsCommand.execute();
    ASSERT_EQ("testAttribute",attribute->getName());
    //test execute again
    editTextOfComponentsCommand.execute();
    ASSERT_EQ("testAttribute",attribute->getName());
}

TEST_F(EditTextOfComponentsCommandTest,testUnexecute){
    Component* attribute = new Attribute("0","testEditAttributeName");
    EditTextOfComponentsCommand editTextOfComponentsCommand = EditTextOfComponentsCommand(attribute,"testAttribute");
    editTextOfComponentsCommand.executionFlag = true;

    attribute->setName("testAttribute");
    editTextOfComponentsCommand.unExecute();
    ASSERT_EQ("testEditAttributeName",attribute->getName());
    //test unexecute again
    editTextOfComponentsCommand.unExecute();
    ASSERT_EQ("testEditAttributeName",attribute->getName());
}