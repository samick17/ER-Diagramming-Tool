#pragma once

#include "Command.h"
#include "Document.h"
#include "Connector.h"
#include "Entity.h"

using namespace std;

class SaveFileCommand : public Command{
public:
	SaveFileCommand(Presentation* presentation);
	~SaveFileCommand();
	
	void execute();
	void unExecute();
private:
	void writeAllComponentsToDoc(Document& doc,vector<Component*> componentVector);
	void writeAllConnectorsToDoc(Document& doc,vector<Component*> componentVector);
	void writeAllPrimaryKeyToDoc(Document& doc,vector<Component*> componentVector);
};