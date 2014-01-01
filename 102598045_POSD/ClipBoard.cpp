#include "ClipBoard.h"
#include "HashMapUtil.h"
#include "Connector.h"
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
    //separate connector and componentMap
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

    HashMap<string,Connector*> connectorMap;
    for each(Connector* connector in ERModelUtil::convertComponentHashMapToTypeHashMap<Connector>(componentMap)){
        string connectorID = connector->getID();
        connectorMap.put(connectorID,connector);
    }

    for each(Connector* connector in connectorMap){
        componentMap.remove(connector->getID());
    }

    for each(Component* component in componentMap)
        clonedComponentMap.put(component->getID(),component->clone());
    //if contains connector's connection , then put connector to componentMap
    for each(Connector* connector in connectorMap){
        string firstConnectedID = connector->getFirstConnectedNode()->getID();
        string secondConnectedID = connector->getSecondConnectedNode()->getID();
        if(componentMap.containsKey(firstConnectedID) &&
            componentMap.containsKey(secondConnectedID)){
                Connector* clonedConnector = static_cast<Connector*>(connector->clone());
                clonedComponentMap.put(connector->getID(),clonedConnector);
                Component* firstNodeInComponentMap = clonedComponentMap.get(firstConnectedID);
                Component* secondNodeInComponentMap = clonedComponentMap.get(secondConnectedID);
                ComponentUtil::connectWithEachOther(firstNodeInComponentMap,secondNodeInComponentMap,clonedConnector);
        }
    }
     return clonedComponentMap;
}