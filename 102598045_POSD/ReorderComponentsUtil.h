#pragma once

#include "ERModel.h"
#include <queue>

class ReorderComponentsUtil{
public:
	ReorderComponentsUtil();
	~ReorderComponentsUtil();

	HashMap<string,Component*> getReorderedComponentMap(ERModel* erModel);
private:
	HashMap<string,Component*> orderedComponentMap;
	HashMap<string,Component*> cloneComponentSet(ERModel* erModel);	
	void reConnectToComponentVector(HashMap<string,Component*> orderedComponentMap);
	void deueueAndInsertToVector(queue<Component*>& componentQueue,HashMap<string,Component*>& orderedComponentMap);
};