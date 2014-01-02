#include "ClipBoard.h"
#include "HashMapUtil.h"
#include "Connector.h"
#include "Node.h"
#include "ComponentUtil.h"
#include "ERModelUtil.h"

ClipBoard::ClipBoard(){
}

ClipBoard::~ClipBoard(){
    HashMapUtil::deleteAll(this->componentMap);
}

void ClipBoard::setData(HashMap<string,Component*> componentMap){
    //clean up
    HashMapUtil::deleteAll(this->componentMap);
    //clone all components, if component can be cloned(consider connector)
    this->componentMap = this->clonedAllComponents(componentMap);
}

HashMap<string,Component*> ClipBoard::getData(){
    return this->clonedAllComponents(this->componentMap);
}

void ClipBoard::clearData(){
    HashMapUtil::deleteAll(this->componentMap);
}

HashMap<string,Component*> ClipBoard::clonedAllComponents(HashMap<string,Component*> componentMap){
    HashMap<string,Component*> clonedComponentMap;
    //separate connector and componentMap
    HashMap<string,Connector*> connectorMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentMap);
    HashMap<string,Node*> nodeMap = ERModelUtil::convertComponentHashMapToTypeHashMap<Node>(componentMap);
    //clone component to result(except connector)
    for each(Component* component in nodeMap)
        clonedComponentMap.put(component->getID(),component->clone());
    //if contains connector's connection , then put connector to componentMap
    for each(Connector* connector in connectorMap){
        string firstConnectedID = connector->getFirstConnectedNode()->getID();
        string secondConnectedID = connector->getSecondConnectedNode()->getID();
        if(nodeMap.containsKey(firstConnectedID) &&
            nodeMap.containsKey(secondConnectedID)){
                Connector* clonedConnector = static_cast<Connector*>(connector->clone());
                clonedComponentMap.put(connector->getID(),clonedConnector);
                Component* firstNodeInComponentMap = clonedComponentMap.get(firstConnectedID);
                Component* secondNodeInComponentMap = clonedComponentMap.get(secondConnectedID);
                ComponentUtil::connectWithEachOther(firstNodeInComponentMap,secondNodeInComponentMap,clonedConnector);
        }
    }
     return clonedComponentMap;
}