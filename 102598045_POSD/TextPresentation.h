#pragma once

#include "Component.h"
#include "Presentation.h"

#define TITLE_WIDTH          26
#define MENU_WIDTH           56
#define COMMAND_KEY_WIDTH     4
#define TABLE_WIDTH          16
#define COLUMN_WIDTH          8

class TextUI;
class InstructionMenu;
class TextUIProcess;

class TextPresentation{
public:    
    TextPresentation(Presentation* presentation);
    ~TextPresentation();

    InstructionMenu* getInstructionMenu();
	//
    void openFile();
    void saveFile();
    void close();
	//display
    void displayDiagram();
    void displayTable();
    void displayComponents();
    void displayConnections();
    void displayEntities();
    void displayEntityAttributes(Entity* entity);

    Component* findComponent();
    Entity* findEntity();
	//instruction
    void processCommand(string commandKey);
    void addNode();
    void deleteComponent();
    void connectTwoNodes();
    void redo();
    void undo();
    void setCardinality(Component* firstNode,Component* secondNode);
    void setNodeName(Node* nodeToSetName);
    void setPrimaryKey();
	//setter
    void setTextUI(TextUI* textUI);
private:
    Presentation* presentation;
    InstructionMenu* instructionMenu;
    TextUI* textUI;
    vector<string> setEntityAttributesPrimaryKey(Entity* entity);
};