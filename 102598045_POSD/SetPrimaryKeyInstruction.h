#pragma once

#include "TextInstruction.h"

class Entity;

class SetPrimaryKeyInstruction : public TextInstruction{
public:
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
	vector<string> SetPrimaryKeyInstruction::setEntityAttributesPrimaryKey(Entity* entity,TextPresentation* textPresentation);
};