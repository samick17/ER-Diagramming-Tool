#pragma once

#include "Presentation.h"

class Receiver{
public:
	Receiver(int key,Presentation* presentation);
	virtual ~Receiver();

	int getKey();

	virtual void response() = 0;
protected:
	Presentation* getPresentation();
private:
	int key;
	Presentation* presentation;
};