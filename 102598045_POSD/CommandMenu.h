#pragma once

#include "CommandData.h"
#include "Presentation.h"
#include "HashMap.h"

typedef CommandData (*getCommandDataByKeyFunc)();

class CommandMenu{
public:
	CommandMenu();
	~CommandMenu();

	HashMap<string,CommandData*> getCommandDataMap();
	CommandData* getCommandDataByKey(string key);
private:
	HashMap<string,CommandData*> commandDataMap;
	void insertCommandData(CommandData* commandData);

	template <typename type>
	static Command* newCommand(Presentation* presentation);
};

template <typename type>
static Command* CommandMenu::newCommand(Presentation* presentation){
	return new type(presentation);
}