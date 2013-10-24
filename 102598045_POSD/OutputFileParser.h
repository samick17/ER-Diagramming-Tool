#pragma once

#include "Document.h"
#include "HashMap.h"
#include "ERModel.h"

class OutputFileParser{
	friend class OutputFileParserTest;
	FRIEND_TEST(OutputFileParserTest,testWriteAllComponentsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllConnectorsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllPrimaryKeyToDoc);
	FRIEND_TEST(OutputFileParserTest,testSerializeComponentToString);
	FRIEND_TEST(OutputFileParserTest,testSerializeEntityToString);
	FRIEND_TEST(OutputFileParserTest,testSerializeConnectorToString);
public:
	OutputFileParser(HashMap<string,Component*> componentMap);
	~OutputFileParser();

	void parseModelToFile(string filePath);
private:
	HashMap<string,Component*> componentMap;
	HashMap<string,string> reorderedIDMap;

	void writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentMap);
	void writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentMap);
	void writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentMap);

	string serializeComponentToString(Component* component);
	string serializeEntityToString(Entity* entity);
	string serializeConnectorToString(Connector* connector);
};