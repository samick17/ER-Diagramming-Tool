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
private:
	void writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentVector);
	void writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentVector);
	void writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentVector);
};