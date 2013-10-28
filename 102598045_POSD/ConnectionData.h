#pragma once

#include <string>

using namespace std;

struct ConnectionData{
public:
    ConnectionData(string connectorID,string connectedFirstNodeID,string connectedSecondNodeID);
    ~ConnectionData();

    string getConnectorID();
    string getConnectedFirstNodeID();
    string getConnectedSecondNodeID();
private:
    string connectorID;
    string connectedFirstNodeID;
    string connectedSecondNodeID;
};