#pragma once

#include "CommandData.h"
#include "Presentation.h"
#include <unordered_map>
#include <vector>

typedef pair<string,CommandData*> CommandDataPair;
typedef CommandData (*getCommandDataByKeyFunc)();

class CommandMenu{
public:
	CommandMenu();
	~CommandMenu();

	vector<CommandData*> getCommandDataVector();
	CommandData* getCommandDataByKey(string key);
private:
	unordered_map<string,CommandData*> commandDataMap;
	vector<string> commandDataKeyOrderVector;
	void insertCommandData(CommandData* commandData);

	template <typename type>
	static Command* newCommand(Presentation* presentation);
};

template <typename type>
static Command* CommandMenu::newCommand(Presentation* presentation){
	return new type(presentation);
}