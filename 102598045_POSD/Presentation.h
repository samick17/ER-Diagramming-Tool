#pragma once

#include "ERModel.h"
#include "Component.h"
#include <QObject>

#define TITLE_WIDTH			26
#define MENU_WIDTH			56
#define COMMAND_KEY_WIDTH	 4
#define TABLE_WIDTH			16
#define COLUMN_WIDTH		 8

class CommandManager;
class Command;
class TextUI;

class Presentation : public QObject{
	Q_OBJECT
public slots:
	void close();
public:	
	Presentation(ERModel* erModel);
	~Presentation();

	ERModel* getERModel();

	string getInput();

	void displayTable();
	void displayComponents();
	void displayConnections();
	void displayEntities();
	void displayEntityAttributes(Entity* entity);

	void processCommand(string commandKey);
	void logMessage(string message,bool nextLine);

	void setCommandManager(CommandManager* commandManager);
	void setTextUI(TextUI* textUI);
	CommandManager* getCommandManager();
private:	
	bool alive;	
	ERModel* erModel;
	CommandManager* commandManager;
	TextUI* textUI;
	void executeCommand(Command* command);
};