#pragma once

#include "ERModel.h"
#include <queue>

class ReorderComponentsUtil{
	friend class ReorderComponentsUtilTest;
	FRIEND_TEST(ReorderComponentsUtilTest,testCloneComponentSet);
	FRIEND_TEST(ReorderComponentsUtilTest,testClearComponentMap);
	FRIEND_TEST(ReorderComponentsUtilTest,testReorderClonedComponents);
public:
	ReorderComponentsUtil();
	~ReorderComponentsUtil();

	HashMap<string,Component*> getReorderedComponentMap(ERModel* erModel);
private:
	HashMap<string,Component*> componentMap;
	HashMap<string,Component*> cloneComponentMap(ERModel* erModel);	
	void clearComponentMap();
	void reConnectToComponentVector();
	HashMap<string,Component*> dequeueAndInsertToVector(queue<Component*>& componentQueue);
};