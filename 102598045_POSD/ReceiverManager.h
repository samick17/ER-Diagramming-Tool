#pragma once

#include "Receiver.h"
#include "HashMap.h"

using namespace std;

class ReceiverManager{
public:
	ReceiverManager();
	virtual ~ReceiverManager();

	void insertReceiver(Receiver* receiver);
	void deleteReceiver(Receiver* receiver);

	void response(int key);
private:
	HashMap<int,Receiver*> receiverMap;
};