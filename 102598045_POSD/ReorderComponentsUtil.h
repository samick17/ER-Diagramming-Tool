#pragma once

#include "ERModel.h"
#include <queue>

class ReorderComponentsUtil{
public:
	ReorderComponentsUtil();
	~ReorderComponentsUtil();

	HashMap<string,Component*> getReorderedComponentMap(ERModel* erModel);
private:
	HashMap<string,Component*> componentMap;
	HashMap<string,Component*> cloneComponentSet(ERModel* erModel);	
	void clearComponentMap();
	void reConnectToComponentVector();
	HashMap<string,Component*> dequeueAndInsertToVector(queue<Component*>& componentQueue);
};