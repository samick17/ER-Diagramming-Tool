#include "EditTextOfComponentsCommand.h"
#include "ERModel.h"
#include "Component.h"

EditTextOfComponentsCommand::EditTextOfComponentsCommand(ERModel* erModel,Component* component,string text) : erModel(erModel),component(component){
    this->originText = component->getName();
    this->textToSet = text;
}

EditTextOfComponentsCommand::~EditTextOfComponentsCommand(){
}

void EditTextOfComponentsCommand::doExecute(){
    this->component->setName(this->textToSet);
}

void EditTextOfComponentsCommand::doUnExecute(){
    this->component->setName(this->originText);
}