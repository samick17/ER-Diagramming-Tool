#include "SaveFileCommand.h"
#include "ReorderComponentsUtil.h"
#include "ERModelUtil.h"
#include <iostream>

SaveFileCommand :: SaveFileCommand(Presentation* presentation) : Command(presentation){	
}

SaveFileCommand::~SaveFileCommand(){
}

void SaveFileCommand :: execute(){	
	this->presentation->logMessage("Please input the file name: ",true);
	
	string filePath = this->presentation->getInput();

	Document doc(filePath);
	
	ERModel* erModel = this->presentation->getERModel();
	//reorder components id
	ReorderComponentsUtil reorderComponentsUtil;
	HashMap<string,Component*> componentVector = reorderComponentsUtil.getReorderedComponentMap(erModel);	

	//write all
	this->writeAllComponentsToDoc(doc,componentVector);
	this->writeAllConnectorsToDoc(doc,componentVector);	
	this->writeAllPrimaryKeyToDoc(doc,componentVector);
	
	doc.saveFile();
}

void SaveFileCommand::unExecute(){
}

void SaveFileCommand::writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentVector){
	for each(Component* component in componentVector){
		string line = component->Component::toString();
		doc.wirteLine(line);
	}
	doc.wirteLine("");
}

void SaveFileCommand::writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentVector){
	HashMap<string,Connector*> connectorSet = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentVector);
	
	for each(Connector* connector in connectorSet){		
		string line = connector->toString();		
		doc.wirteLine(line);
	}
	doc.wirteLine("");
}

void SaveFileCommand::writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentSet){
	HashMap<string,Entity*> entitySet = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(componentSet);

	for each(Entity* entity in entitySet){
		string line = entity->toString();		
		doc.wirteLine(line);
	}
}