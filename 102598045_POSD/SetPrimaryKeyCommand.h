#pragma once

#include "Command.h"
#include "Entity.h"
#include <set>

class SetPrimaryKeyCommand : public Command{
public:
	SetPrimaryKeyCommand(Presentation* presentation);
	~SetPrimaryKeyCommand();
	
	void execute();

	set<string> setEntityAttributesPrimaryKey(Entity* entity);
};