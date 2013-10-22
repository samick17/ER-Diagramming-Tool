#pragma once

#include "Receiver.h"
#include "HashMap.h"

using namespace std;

class ReceiverManager{
	friend class ReceiverManagerTest;
	FRIEND_TEST(ReceiverManagerTest,testInsertReceiver);
	FRIEND_TEST(ReceiverManagerTest,testDeleteReceiver);
public:
	ReceiverManager();
	virtual ~ReceiverManager();

	void insertReceiver(Receiver* receiver);
	void deleteReceiver(Receiver* receiver);

	void response(int key);
private:
	HashMap<int,Receiver*> receiverMap;
};