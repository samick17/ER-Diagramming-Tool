#pragma once

#include "Presentation.h"

class TextUI{
public:	
	TextUI(Presentation* presentation);
	~TextUI();
	
	void displayMenu();
	void displayTitle(string title);
	void displayTable(HashMap<string,Table*> tableMap);
	void displayComponents(HashMap<string,Component*> componentMap);
	void displayConnections(HashMap<string,Connector*> connectorMap);
	void displayEntities(HashMap<string,Component*> entityMap);
	void displayEntityAttributes(Entity* entity,HashMap<string,Component*> attributesMap);
	void displayDiagram();
	void displayComponentMap(HashMap<string,Component*> componentMap);	
	void displayStringWithComma(string strStart,vector<string> stringVector,string strEnd);
	void processCommand();

	void alertException(string infomation);
private:
	Presentation* presentation;
};