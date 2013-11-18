#include "ReorderComponentsUtil.h"
#include "StringUtil.h"
#include "ComponentUtil.h"

HashMap<string,string> ReorderComponentsUtil::getReorderedComponentIDMap(HashMap<string,Component*> componentMap){
    HashMap<string,string> orderedComponentIDMap;
    int index = 0;
    for each(Component* component in componentMap){
        orderedComponentIDMap.put(component->getID(),StringUtil::intToString(index));
        index++;
    }
    return orderedComponentIDMap;
}