#include "StateTest.h"

void StateTest::SetUp(){
    this->presentation = new Presentation(&this->erModel);
    this->graphicalPresentation = new GraphicalPresentation(this->presentation);
}

void StateTest::TearDown(){
    delete this->presentation;
    delete this->graphicalPresentation;
}