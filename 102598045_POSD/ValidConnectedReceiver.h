#pragma once

#include "Receiver.h"

class ValidConnectedReceiver : public Receiver{
public:
	ValidConnectedReceiver(int key,Presentation* presentation,Component* firstNode,Component* secondNode);
	~ValidConnectedReceiver();

	void response();
private:
	Component* firstNode;
	Component* secondNode;
};