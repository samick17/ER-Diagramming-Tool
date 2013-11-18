#pragma once

class Command;
class ERModel;
class Node;
class Connector;
class Component;

class CommandFactory{
public:
    Command* createAddNodeCommand(ERModel* erModel,Node* node);
    Command* createConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector);
    Command* createDeleteComponentCommand(ERModel* erModel,Component* component);
};