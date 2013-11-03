#pragma once

#include "Component.h"
#include "Presentation.h"

#define TITLE_WIDTH          26
#define MENU_WIDTH           56
#define COMMAND_KEY_WIDTH     4
#define TABLE_WIDTH          16
#define COLUMN_WIDTH          8

class InstructionMenu;
class TextUIPresenter;

class TextPresentation{
public:
    TextPresentation(Presentation* presentation);
    ~TextPresentation();

    string getInput();
    InstructionMenu* getInstructionMenu();
    TextUIPresenter* getTextUIPresenter();

    void displayMenu();
    void processCommand();
    HashMap<string,Table*> getAllTables();
    HashMap<string,Component*> getAllComponents();
    HashMap<string,Connector*> getAllConnections();
    HashMap<string,Component*> getAllEntities();
    HashMap<string,Component*> getEntityAttributes(Entity* entity);

    Component* findComponent();
    Entity* findEntity();

    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    Node* addNode(string nodeType);
    void deleteComponent(Component* componentToDelete);
    int connectTwoNodes(Component* firstNode,Component* secondNode);
    void setCardinality(Component* firstNode,Component* secondNode,string relationName);
    void redo();
    void undo();
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
private:
    Presentation* presentation;
    TextUIPresenter* textUIPresenter;
    InstructionMenu* instructionMenu;
    
};