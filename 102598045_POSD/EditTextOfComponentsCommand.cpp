#include "EditTextOfComponentsCommand.h"
#include "ERModel.h"
#include "Component.h"

EditTextOfComponentsCommand::EditTextOfComponentsCommand(Component* component,string text) : component(component){
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