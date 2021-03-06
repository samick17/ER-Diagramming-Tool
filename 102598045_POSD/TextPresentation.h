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
    string getCardinality(string input);

    Component* findComponent();
    Entity* findEntity();

    bool isNeedToSave();
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    Node* addNode(string nodeType);
    void deleteComponent(string input);
    int connectTwoNodes(Component* firstNode,Component* secondNode);
    void setCardinality(Component* firstNode,Component* secondNode,string cardinality);
    void setPrimaryKey(string componentID);
    void redo();
    void undo();
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);
    void executeSync(string syncEventType);
private:
    void initialSyncMap();
    void initialCardinalityInputMap();
    Presentation* presentation;
    TextUIPresenter* textUIPresenter;
    InstructionMenu* instructionMenu;
    typedef void (TextUIPresenter::*ViewSyncFunction)();
    HashMap<string,ViewSyncFunction> syncMap;
    HashMap<string,string> cardinalityInputMap;
};