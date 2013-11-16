#pragma once

#include <string>

using namespace std;

class ControllerEvent{
public:
    static const string OpenFile;
    static const string SaveFile;
    static const string AddNode;
    static const string ConnectTwoNodes;
    static const string DisplayDiagram;
    static const string SetPrimaryKey;
    static const string DisplayTable;
    static const string DeleteComponent;
    static const string Undo;
    static const string Redo;
    static const string Close;
};