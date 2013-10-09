#pragma once

#include "ReceiverManager.h"

class ConnectionReceiverManager : public ReceiverManager{
public:
	ConnectionReceiverManager(Presentation* presentation,Component* firstNode,Component* secondNode);
	~ConnectionReceiverManager();
};