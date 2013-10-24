#pragma once

#include "Component.h"
#include <queue>

class ReorderComponentsUtil{
public:
	static HashMap<string,string> getReorderedComponentIDMap(HashMap<string,Component*> componentMap);	
};