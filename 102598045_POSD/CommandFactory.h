#pragma once

#include <string>

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
    Command* createSetPrimaryKeyCommand(ERModel* erModel,Attribute* attribute);
    Command* createEditTextOfComponentsCommand(ERModel* erModel,Component* component,string text);
};