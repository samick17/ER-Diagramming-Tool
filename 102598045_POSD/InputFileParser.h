#pragma once

#include "Document.h"
#include "Component.h"
#include "ERModel.h"
#include "ConnectionData.h"
#include <queue>

using namespace std;

typedef pair<string,string> StringPair;

class InputFileParser{
    friend class InputFileParserTest;
    FRIEND_TEST(InputFileParserTest,testLoadAllComponentsFromDoc);
    FRIEND_TEST(InputFileParserTest,testLoadAllConnectorsFromDoc);
    FRIEND_TEST(InputFileParserTest,testLoadAllPrimaryKeyAndSetUpFromDoc);
    FRIEND_TEST(InputFileParserTest,testAddAllComponentToERModel);
    FRIEND_TEST(InputFileParserTest,testAddConnector);
    FRIEND_TEST(InputFileParserTest,testIsQueueArriveConnectionDataID);
public:
    InputFileParser();
    ~InputFileParser();

    void parseFileToModel(string fileName,string fileExtension,ERModel* erModel);
private:
    void loadAllComponentsFromDoc(Document& document);
    void loadAllConnectorsFromDoc(Document& document);
    void loadAllPrimaryKeyAndSetUpFromDoc(Document& document);
    void addAllComponentToERModel();
    void addConnector(ConnectionData connectionData,string connectionName);
    bool isQueueArriveConnectionDataID(int id);
    void loadPosDocAndSetComponentsPosition(string fileName);
    ERModel* erModel;
    queue<StringPair> componentDataQueue;
    queue<ConnectionData> connectionDataQueue;
};