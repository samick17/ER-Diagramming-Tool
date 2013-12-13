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

using namespace std;

class CommandFactory{
public:
    Command* createAddNodeCommand(ERModel* erModel,Node* node);
    Command* createConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector);
    Command* createDeleteComponentCommand(ERModel* erModel,Component* component);
    Command* createSetPrimaryKeyCommand(Attribute* attribute);
    Command* createEditTextOfComponentsCommand(Component* component,string text);
    Command* createMoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition);
};