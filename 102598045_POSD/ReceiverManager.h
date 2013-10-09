#pragma once

#include "Receiver.h"
#include <hash_map>

using namespace std;

typedef pair<int,Receiver*> ReceiverPair;

class ReceiverManager{
public:
	ReceiverManager();
	virtual ~ReceiverManager();

	void insertReceiver(Receiver* receiver);
	void deleteReceiver(Receiver* receiver);

	void response(int key);
private:
	hash_map<int,Receiver*> receiverMap;
};