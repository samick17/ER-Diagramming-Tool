#pragma once

#include <string>

using namespace std;

class ActionData{
public:
    static const string ActionName[];
    static const string ActionIconPath[];
    static const string ActionShortCutKey[];

    static const unsigned int ActionLength;
    static const unsigned int OpenFile;
    static const unsigned int SaveFile;
    static const unsigned int SaveXmlFile;
    static const unsigned int Exit;
    static const unsigned int Undo;
    static const unsigned int Redo;
    static const unsigned int Delete;
    static const unsigned int Cut;
    static const unsigned int Copy;
    static const unsigned int Paste;
    static const unsigned int PointerState;
    static const unsigned int ConnectState;
    static const unsigned int AddAttributeState;
    static const unsigned int AddEntityState;
    static const unsigned int AddRelationShipState;
    static const unsigned int SetPrimaryKeyState;
    static const unsigned int BrowseDB;
    static const unsigned int About;
};