#pragma once

#include "Command.h"
#include "Entity.h"
#include <vector>

class SetPrimaryKeyCommand : public Command{
public:
	SetPrimaryKeyCommand(Presentation* presentation);
	~SetPrimaryKeyCommand();
	
	void execute();

	vector<string> setEntityAttributesPrimaryKey(Entity* entity);
};