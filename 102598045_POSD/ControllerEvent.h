#pragma once

class ControllerEvent{
public:
    static const int OpenFile;
    static const int SaveFile;
    static const int AddNode;
    static const int ConnectTwoNodes;
    static const int DisplayDiagram;
    static const int SetPrimaryKey;
    static const int DisplayTable;
    static const int DeleteComponent;
    static const int Undo;
    static const int Redo;
    static const int Close;
};