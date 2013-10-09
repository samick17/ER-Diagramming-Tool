#pragma once

#include "Receiver.h"

class ConnectedERReceiver : public Receiver{
public:
	ConnectedERReceiver(int key,Presentation* presentation,Component* firstNode,Component* secondNode);
	~ConnectedERReceiver();

	void response();
private:
	Component* firstNode;
	Component* secondNode;
};