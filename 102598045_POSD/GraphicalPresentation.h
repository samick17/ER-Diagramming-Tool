#pragma once

#include "Component.h"
#include "Presentation.h"
#include "WidgetFactory.h"
#include <QList>

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,ComponentWidget*> getAllComponentWidgets();

    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(ComponentWidget* selectedWidget);
    void selectWidget(ComponentWidget* selectedWidget);
    void keyCtrlPressed();
    void keyCtrlReleased();
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify(int notifiedEventType);
    void notify(IObserver* observer,int notifiedEventType);
private:
    Presentation* presentation;
    HashMap<string,ComponentWidget*> componentWidgetMap;
    QList<ComponentWidget*> selectedWidgetList;
    bool isCtrlPressed;
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