#include "ComponentVisitor.h"
#include "Component.h"

ComponentVisitor::ComponentVisitor(HashMap<string,string> reorderedIDMap) : reorderedIDMap(reorderedIDMap){
}

ComponentVisitor::~ComponentVisitor(){
}

string ComponentVisitor::getTransformedID(Component* component){
    return this->reorderedIDMap.get(component->getID());
}