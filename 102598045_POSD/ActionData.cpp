#include "ActionData.h"

const string ActionData::ActionName[] = {"Open...","Exit","Undo","Redo","Delete","Cut","Copy","Paste","Pointer","AddConnector","AddAttribute","AddEntity","AddRelationShip","SetPrimaryKey","browseTable","About"};
const string ActionData::ActionIconPath[] = {":/res/Resources/open.png",":/res/Resources/exit.png",":/res/Resources/undo.png",":/res/Resources/redo.png",
                                             ":/res/Resources/delete",":/res/Resources/cut",":/res/Resources/copy",":/res/Resources/paste",
                                             ":/res/Resources/cursor.png",":/res/Resources/connector.png",":/res/Resources/attribute.png",
                                             ":/res/Resources/entity.png",":/res/Resources/relationship.png",":/res/Resources/key.png",
                                             ":/res/Resources/browseDB.png",":/res/Resources/about.png"};
const string ActionData::ActionShortCutKey[] = {"Ctrl+O","Alt+F4","Ctrl+Z","Ctrl+Y","Del","Ctrl+X","Ctrl+C","Ctrl+V","","","","","","","",""};

const unsigned int ActionData::ActionLength = 16;
const unsigned int ActionData::OpenFile = 0;
const unsigned int ActionData::Exit = 1;
const unsigned int ActionData::Undo = 2;
const unsigned int ActionData::Redo = 3;
const unsigned int ActionData::Delete = 4;
const unsigned int ActionData::Cut = 5;
const unsigned int ActionData::Copy = 6;
const unsigned int ActionData::Paste = 7;
//State Action
const unsigned int ActionData::PointerState = 8;
const unsigned int ActionData::ConnectState = 9;
const unsigned int ActionData::AddAttributeState = 10;
const unsigned int ActionData::AddEntityState = 11;
const unsigned int ActionData::AddRelationShipState = 12;
const unsigned int ActionData::SetPrimaryKeyState = 13;
const unsigned int ActionData::BrowseDB = 14;
//Help
const unsigned int ActionData::About = 15;