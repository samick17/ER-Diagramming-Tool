#include "ActionData.h"

const string ActionData::ActionName[] = {"Open...","Exit","Undo","Redo","Delete","Pointer","AddConnector","AddAttribute","AddEntity","AddRelationShip","SetPrimaryKey"};
const string ActionData::ActionIconPath[] = {":/res/Resources/open.png",":/res/Resources/exit.png",":/res/Resources/undo.png",":/res/Resources/redo.png",
                                             ":/res/Resources/delete",":/res/Resources/cursor.png",":/res/Resources/connector.png",":/res/Resources/attribute.png",
                                             ":/res/Resources/entity.png",":/res/Resources/relationship.png",":/res/Resources/key.png"};
const string ActionData::ActionShortCutKey[] = {"Ctrl+O","Alt+F4","Ctrl+Z","Ctrl+Y","Delete","","","","","",""};

const unsigned int ActionData::ActionLength = 11;
const unsigned int ActionData::OpenFile = 0;
const unsigned int ActionData::Exit = 1;
const unsigned int ActionData::Undo = 2;
const unsigned int ActionData::Redo = 3;
const unsigned int ActionData::Delete = 4;
//State Action
const unsigned int ActionData::PointerState = 5;
const unsigned int ActionData::ConnectState = 6;
const unsigned int ActionData::AddAttributeState = 7;
const unsigned int ActionData::AddEntityState = 8;
const unsigned int ActionData::AddRelationShipState = 9;
const unsigned int ActionData::SetPrimaryKeyState = 10;