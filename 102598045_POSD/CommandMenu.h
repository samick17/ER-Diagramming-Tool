#pragma once

#include "CommandData.h"
#include "Presentation.h"
#include "HashMap.h"

class CommandMenu{
	friend class CommandMenuTest;
	FRIEND_TEST(CommandMenuTest,testInsertCommandData);
	FRIEND_TEST(CommandMenuTest,testNewCommand);
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