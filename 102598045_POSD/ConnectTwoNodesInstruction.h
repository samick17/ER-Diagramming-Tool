#pragma once

#include "TextInstruction.h"

class Component;

class ConnectTwoNodesInstruction : public TextInstruction{
public:
    ConnectTwoNodesInstruction();
    ~ConnectTwoNodesInstruction();
    virtual void execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter);
private:
	void ConnectTwoNodesInstruction::setCardinality(Component* firstNode,Component* secondNode,TextPresentation* textPresentation);
};