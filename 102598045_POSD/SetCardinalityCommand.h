#pragma once

#include "Command.h"
#include "HashMap.h"

class SetCardinalityCommand : public Command{
public:
	SetCardinalityCommand(Presentation* presentation,Component* firstNode,Component* secondNode);
	~SetCardinalityCommand();
	
	void execute();
private:
	HashMap<string,string> cardinalityPairMap;
	Component* firstNode;
	Component* secondNode;
};