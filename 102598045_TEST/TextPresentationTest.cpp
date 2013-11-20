#include "TextPresentationTest.h"
#include "EmptyCollectionException.h"
#include "ComponentType.h"

void TextPresentationTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->textPresentation = new TextPresentation(this->presentation);
}

void TextPresentationTest::TearDown(){
    delete this->textPresentation;
    delete this->presentation;
}

TEST_F(TextPresentationTest,testGetTables){
    ASSERT_THROW(this->textPresentation->getAllTables(),EmptyCollectionException);
}

TEST_F(TextPresentationTest,testGetAllComponents){
    ASSERT_THROW(this->textPresentation->getAllComponents(),EmptyCollectionException);
}

TEST_F(TextPresentationTest,testGetAllConnections){
    ASSERT_THROW(this->textPresentation->getAllConnections(),EmptyCollectionException);
}

TEST_F(TextPresentationTest,testGetAllEntities){
    ASSERT_THROW(this->textPresentation->getAllEntities(),EmptyCollectionException);
}

TEST_F(TextPresentationTest,testGetEntityAttributes){
    Entity* entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    ASSERT_THROW(this->textPresentation->getEntityAttributes(entity),EmptyCollectionException);
}