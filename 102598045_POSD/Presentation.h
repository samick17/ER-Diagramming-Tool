#pragma once

#include <set>
#include "ERModel.h"
#include "Component.h"

#define TITLE_WIDTH			26
#define MENU_WIDTH			56
#define COMMAND_KEY_WIDTH	 4
#define TABLE_WIDTH			16
#define COLUMN_WIDTH		 8

class CommandManager;
class Command;

class Presentation{
public:	
	Presentation(ERModel* erModel);
	~Presentation();

	ERModel* getERModel();

	bool isAlive();
	void close();

	string getInput();

	void displayMenu();
	void displayTitle(string title);	
	void displayTable();
	void displayComponents();
	void displayConnections();
	void displayEntities();
	void displayEntityAttributes(Entity* entity);
	void displayStringWithComma(string strStart,set<string> stringSet,string strEnd);

	void displayCommandInfoAndSetUp(Command* command);
	void processCommand(string commandKey);
	void logMessage(string message,bool nextLine);

	void setCommandManager(CommandManager* commandManager);
	CommandManager* getCommandManager();
private:	
	bool alive;	
	ERModel* erModel;
	CommandManager* commandManager;
	void displayComponentSet(HashMap<string,Component*> componentSet);
};