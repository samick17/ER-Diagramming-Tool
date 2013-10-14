#include "ReceiverManager.h"

ReceiverManager::ReceiverManager(){
}

ReceiverManager::~ReceiverManager(){
	for each(ReceiverPair receiverPair in this->receiverMap)	{
		delete receiverPair.second;		
		receiverPair.second = NULL;
	}
	this->receiverMap.clear();
}

void ReceiverManager::insertReceiver(Receiver* receiver){
	this->receiverMap.insert(ReceiverPair(receiver->getKey(),receiver));
}

void ReceiverManager::deleteReceiver(Receiver* receiver){
	this->receiverMap.erase(receiver->getKey());
	delete receiver;
	receiver = NULL;
}

void ReceiverManager::response(int key){	
	hash_map<int,Receiver*>::iterator receiverIterator;
	if((receiverIterator = this->receiverMap.find(key)) != this->receiverMap.end())	
		receiverIterator->second->response();
}