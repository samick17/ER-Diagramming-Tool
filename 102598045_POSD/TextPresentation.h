#pragma once

#include "Component.h"

#define TITLE_WIDTH          26
#define MENU_WIDTH           56
#define COMMAND_KEY_WIDTH     4
#define TABLE_WIDTH          16
#define COLUMN_WIDTH          8

class Node;
class Entity;
class ERModel;
class Command;
class TextUI;

class TextPresentation{
public:    
    TextPresentation(ERModel* erModel);
    ~TextPresentation();

    ERModel* getERModel();

    void openFile();
    void saveFile();
    void close();

    void displayDiagram();
    void displayTable();
    void displayComponents();
    void displayConnections();
    void displayEntities();
    void displayEntityAttributes(Entity* entity);

    Component* findComponent();
    Entity* findEntity();

    void processCommand(string commandKey);
    void addNode();
    void deleteComponent();
    void connectTwoNodes();
    void redo();
    void undo();
    void setCardinality(Component* firstNode,Component* secondNode);
    void setNodeName(Node* nodeToSetName);
    void setPrimaryKey();

    void setTextUI(TextUI* textUI);
private:    
    bool alive;
    ERModel* erModel;
    TextUI* textUI;
    vector<string> setEntityAttributesPrimaryKey(Entity* entity);
};