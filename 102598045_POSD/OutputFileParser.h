#pragma once

#include "Document.h"
#include "HashMap.h"
#include "ERModel.h"

class OutputFileParser{
	friend class OutputFileParserTest;
	FRIEND_TEST(OutputFileParserTest,testWriteAllComponentsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllConnectorsToDoc);
	FRIEND_TEST(OutputFileParserTest,testWriteAllPrimaryKeyToDoc);
public:
	OutputFileParser();
	~OutputFileParser();

	void parseModelToFile(string filePath,ERModel* erModel);
private:
	void writeAllComponentsToDoc(Document& doc,HashMap<string,Component*> componentMap);
	void writeAllConnectorsToDoc(Document& doc,HashMap<string,Component*> componentMap);
	void writeAllPrimaryKeyToDoc(Document& doc,HashMap<string,Component*> componentMap);
};