#pragma once

#include "ERModel.h"
#include <queue>

class ReorderComponentsUtil{
public:
	ReorderComponentsUtil();
	~ReorderComponentsUtil();

	vector<Component*> getReorderedComponentVector(ERModel* erModel);
private:
	vector<Component*> reorderedComponentVector;
	vector<Component*> cloneComponentSet(ERModel* erModel);	
	void reConnectToComponentVector(vector<Component*> orderedComponentVector);
	void deueueAndInsertToVector(queue<Component*>& componentQueue,vector<Component*>& orderedComponentVector);
};