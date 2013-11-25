#include "SetPrimaryKeyCommand.h"
#include "Attribute.h"

SetPrimaryKeyCommand::SetPrimaryKeyCommand(ERModel* erModel,Attribute* attribute) : erModel(erModel),attribute(attribute){
    isPrimaryKey = attribute->isPrimaryKey();
}

SetPrimaryKeyCommand::~SetPrimaryKeyCommand(){
}

void SetPrimaryKeyCommand::doExecute(){
    if(isPrimaryKey)
        attribute->setAsDefaultKey();
    else 
        attribute->setAsPrimaryKey();
}

void SetPrimaryKeyCommand::doUnExecute(){
    if(isPrimaryKey)
        attribute->setAsPrimaryKey();
    else 
        attribute->setAsDefaultKey();
}