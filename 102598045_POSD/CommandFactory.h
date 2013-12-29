#pragma once

#include <string>
#include "Point.h"
#include "HashMap.h"

class Command;
class ERModel;
class Attribute;
class Node;
class Connector;
class Component;
class ClipBoard;

using namespace std;

class CommandFactory{
public:
    Command* createAddNodeCommand(HashMap<string,Component*>& componentMap,Node* node);
    Command* createConnectNodeCommand(HashMap<string,Component*>& componentMap,Component* firstNode,Component* secondNode,Connector* connector);
    Command* createDeleteMultiComponentCommand(HashMap<string,Component*>& componentMap,HashMap<string,Component*> componentMapToDelete);
    Command* createSetPrimaryKeyCommand(Attribute* attribute);
    Command* createEditTextOfComponentsCommand(Component* component,string text);
    Command* createMoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition);
    Command* createCutComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,HashMap<string,Component*> componentMapToCut);
    Command* createPasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,int* newComponentID,int pasteCount);
};