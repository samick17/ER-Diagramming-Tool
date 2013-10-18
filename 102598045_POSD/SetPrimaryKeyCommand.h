#pragma once

#include "Command.h"
#include "Entity.h"
#include <set>

class SetPrimaryKeyCommand : public Command{
public:
	SetPrimaryKeyCommand(Presentation* presentation);
	~SetPrimaryKeyCommand();
	
	void execute();

	vector<string> askPrimaryKeyAttributesID(Entity* entity);
};