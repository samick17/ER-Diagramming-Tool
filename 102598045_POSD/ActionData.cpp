#include "ActionData.h"

const string ActionData::ActionName[] = {"Open","Save","Save As","Exit","Undo","Redo","Delete","Cut","Copy","Paste","Pointer","AddConnector","AddAttribute","AddEntity","AddRelationShip","SetPrimaryKey","BrowseTable","About"};
const string ActionData::ActionIconPath[] = {":/res/Resources/open.png",":/res/Resources/save.png",":/res/Resources/save_as.png",":/res/Resources/exit.png",":/res/Resources/undo.png",":/res/Resources/redo.png",
                                             ":/res/Resources/delete",":/res/Resources/cut",":/res/Resources/copy",":/res/Resources/paste",
                                             ":/res/Resources/cursor.png",":/res/Resources/connector.png",":/res/Resources/attribute.png",
                                             ":/res/Resources/entity.png",":/res/Resources/relationship.png",":/res/Resources/key.png",
                                             ":/res/Resources/browseDB.png",":/res/Resources/about.png"};
const string ActionData::ActionShortCutKey[] = {"Ctrl+O","Ctrl+S","","Ctrl+E","Ctrl+Z","Ctrl+Y","Del","Ctrl+X","Ctrl+C","Ctrl+V","","","","","","","",""};

const unsigned int ActionData::ActionLength = 18;
const unsigned int ActionData::OpenFile = 0;
const unsigned int ActionData::SaveFile = 1;
const unsigned int ActionData::SaveXmlFile = 2;
const unsigned int ActionData::Exit = 3;
const unsigned int ActionData::Undo = 4;
const unsigned int ActionData::Redo = 5;
const unsigned int ActionData::Delete = 6;
const unsigned int ActionData::Cut = 7;
const unsigned int ActionData::Copy = 8;
const unsigned int ActionData::Paste = 9;
//State Action
const unsigned int ActionData::PointerState = 10;
const unsigned int ActionData::ConnectState = 11;
const unsigned int ActionData::AddAttributeState = 12;
const unsigned int ActionData::AddEntityState = 13;
const unsigned int ActionData::AddRelationShipState = 14;
const unsigned int ActionData::SetPrimaryKeyState = 15;
const unsigned int ActionData::BrowseDB = 16;
//Help
const unsigned int ActionData::About = 17;