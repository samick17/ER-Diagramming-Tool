#pragma once

#include "Component.h"
#include "Presentation.h"
#include "ComponentWidgetData.h"
#include <QPointF>
#include <set>

class State;
class StateSubject;

class GraphicalPresentation {
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,ComponentWidgetData> getAllComponentWidgetDatas();
    State* getState();
    StateSubject* getStateSubject();

    void addNode(string nodeType,QPointF position);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(string componentID);
    void selectWidget(string componentID);
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);
    void sync(ISynchronizer* synchronizer,int syncEventType);
    //register
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
private:
    Presentation* presentation;
    HashMap<string,ComponentWidgetData> componentDataMap;
    set<string> selectedWidgetSet;
    bool isCtrlPressed;
    StateSubject* stateSubject;

    void clearAllComponentWidget();
    void updateComponentWidgetMap();
    int createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap,int& currentHeight);
    int createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& currentHeight);
    int createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight);
    void createConnectorWidget(HashMap<string,Component*>& componentMap,HashMap<string,Connector*> connectorMap);
    void createRemainsEntityWidget(HashMap<string,Component*>& componentMap,int& currentHeight);
    void createRemainsAttributeWidget(HashMap<string,Component*>& componentMap,int& currentHeight);
};