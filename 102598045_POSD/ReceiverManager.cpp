#include "ReceiverManager.h"

ReceiverManager::ReceiverManager(){
}

ReceiverManager::~ReceiverManager(){
	for each(Receiver* receiver in this->receiverMap)	{
		delete receiver;
	}
}

void ReceiverManager::insertReceiver(Receiver* receiver){
	this->receiverMap.put(receiver->getKey(),receiver);
}

void ReceiverManager::deleteReceiver(Receiver* receiver){
	this->receiverMap.remove(receiver->getKey());
	delete receiver;
}

void ReceiverManager::response(int key){		
	if(this->receiverMap.containsKey(key))
		this->receiverMap.get(key)->response();
}