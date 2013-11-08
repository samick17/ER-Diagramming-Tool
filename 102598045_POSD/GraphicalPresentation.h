#pragma once

#include "Component.h"
#include "Presentation.h"
#include "WidgetFactory.h"
#include <QList>

class State;

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,ComponentWidget*> getAllComponentWidgets();
    State* getState();

    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(ComponentWidget* selectedWidget);
    void selectWidget(ComponentWidget* selectedWidget);
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);
    void sync(ISynchronizer* synchronizer,int syncEventType);
private:
    Presentation* presentation;
    HashMap<string,ComponentWidget*> componentWidgetMap;
    QList<ComponentWidget*> selectedWidgetList;
    bool isCtrlPressed;
    State* state;

    void clearAllComponentWidget();
    void updateComponentWidgetMap();
    int createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap,int& currentHeight);
    int createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& currentHeight);
    int createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight);
    void createConnectorWidget(HashMap<string,Connector*> connectorMap);
    void setConnectorWidgetProperty(ConnectorWidget* connectorWidget,ComponentWidget* sourceWidget,ComponentWidget* targetWidget);
    void createRemainsEntityWidget(HashMap<string,Component*>& componentMap,int& currentHeight);
    void createRemainsAttributeWidget(HashMap<string,Component*>& componentMap,int& currentHeight);
};