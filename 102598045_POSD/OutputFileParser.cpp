#include "OutputFileParser.h"
#include "ERModelUtil.h"
#include "StringSymbol.h"
#include "ReorderComponentsUtil.h"
#include "StringUtil.h"

OutputFileParser::OutputFileParser(HashMap<string,Component*> componentMap) : componentMap(componentMap){
	//reorder components id
	this->reorderedIDMap = ReorderComponentsUtil::getReorderedComponentIDMap(this->componentMap);
}

OutputFileParser::~OutputFileParser(){
}

void OutputFileParser::parseModelToFile(string filePath){
	Document doc(filePath);		
	//write all
	this->writeAllComponentsToDoc(doc,componentMap);
	this->writeAllConnectorsToDoc(doc,componentMap);	
	this->writeAllPrimaryKeyToDoc(doc,componentMap);
	
	doc.saveFile();
}

void OutputFileParser::writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentMap){
	for each(Component* component in componentMap){
		string line = this->serializeComponentToString(component);
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}

void OutputFileParser::writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentMap){
	HashMap<string,Connector*> connectorSet = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentMap);
	
	for each(Connector* connector in connectorSet){
		string line = this->serializeConnectorToString(connector);
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}

void OutputFileParser::writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentMap){
	HashMap<string,Entity*> entitySet = ERModelUtil::convertComponentHashMapToTypeHashMap<Entity>(componentMap);

	for each(Entity* entity in entitySet){
		string line = serializeEntityToString(entity);
		if(line == StringSymbol::Empty)
			continue;
		doc.wirteLine(line);
	}
	doc.wirteLine(StringSymbol::Empty);
}

string OutputFileParser::serializeComponentToString(Component* component){
	string name = component->getName();
	string type = component->getType();
	if(name == StringSymbol::Empty)
		return type;
	string result = type+StringSymbol::Comma+StringSymbol::Space +name;
	return result;
}

string OutputFileParser::serializeEntityToString(Entity* entity){
	HashMap<string,Attribute*> primaryKeyAttributeHashMap = entity->getPrimaryKeyAttributes();

	if(primaryKeyAttributeHashMap.empty())
		return StringSymbol::Empty;

	string result = reorderedIDMap.get(entity->getID());
	vector<string> primaryKeyAttributeIDVector;

	for each(Attribute* attribute in primaryKeyAttributeHashMap)	
		primaryKeyAttributeIDVector.push_back(reorderedIDMap.get(attribute->getID()));	

	result += StringSymbol::Space+StringUtil::appendWithComma(primaryKeyAttributeIDVector);
	return result;
}

string OutputFileParser::serializeConnectorToString(Connector* connector){
	string result = reorderedIDMap.get(connector->getID());
	result += StringSymbol::Space;
	result += reorderedIDMap.get(connector->getFirstConnectedNode()->getID());
	connector->getFirstConnectedNode()->getName();
	result += StringSymbol::Comma;
	result += reorderedIDMap.get(connector->getSecondConnectedNode()->getID());

	return result;
}