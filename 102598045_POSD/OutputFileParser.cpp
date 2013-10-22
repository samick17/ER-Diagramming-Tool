#include "OutputFileParser.h"
#include "ERModelUtil.h"
#include "StringSymbol.h"
#include "ReorderComponentsUtil.h"

OutputFileParser::OutputFileParser(){
}

OutputFileParser::~OutputFileParser(){
}

void OutputFileParser::parseModelToFile(string filePath,ERModel* erModel){
	Document doc(filePath);
	
	//reorder components id
	ReorderComponentsUtil reorderComponentsUtil;
	HashMap<string,Component*> componentVector = reorderComponentsUtil.getReorderedComponentMap(erModel);	

	//write all
	this->writeAllComponentsToDoc(doc,componentVector);
	this->writeAllConnectorsToDoc(doc,componentVector);	
	this->writeAllPrimaryKeyToDoc(doc,componentVector);
	
	doc.saveFile();
}

void OutputFileParser::writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentMap){
	for each(Component* component in componentMap){
		string line = component->Component::toString();
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}

void OutputFileParser::writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentMap){
	HashMap<string,Connector*> connectorSet = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentMap);
	
	for each(Connector* connector in connectorSet){		
		string line = connector->toString();		
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}

void OutputFileParser::writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentMap){
	HashMap<string,Entity*> entitySet = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(componentMap);

	for each(Entity* entity in entitySet){
		string line = entity->toString();
		if(line == StringSymbol::Empty)
			continue;
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}