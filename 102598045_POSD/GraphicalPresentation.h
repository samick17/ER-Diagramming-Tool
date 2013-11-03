#pragma once

#include "Component.h"
#include "Presentation.h"
#include "WidgetFactory.h"
#include <QList>

class GraphicalUI;

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,ComponentWidget*> getAllComponentWidgets();

    void openFile();
    void saveFile();
    void close();
    bool isSelected(ComponentWidget* selectedWidget);
    void selectWidget(ComponentWidget* selectedWidget);
    void keyCtrlPressed();
    void keyCtrlReleased();
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
private:
    Presentation* presentation;
    GraphicalUI* graphicalUI;
    HashMap<string,ComponentWidget*> componentWidgetMap;
    QList<ComponentWidget*> selectedWidgetList;
    bool isCtrlPressed;
    void clearAllComponentWidget();
    void updateComponentWidgetMap();
    void createRelationShipWidget(HashMap<string,Component*>& componentMap,HashMap<string,RelationShip*> relationShipMap);
    void createEntityWidget(HashMap<string,Component*>& componentMap,HashMap<string,Entity*> entityMap,int& relationShipHeight);
    void createAttributeWidget(HashMap<string,Component*>& componentMap,HashMap<string,Attribute*> attributeMap,int& attributeHeight);
    void createConnectorWidget(HashMap<string,Connector*> connectorMap);
    void setConnectorWidget(ConnectorWidget* connectorWidget,ComponentWidget* sourceWidget,ComponentWidget* targetWidget);
    void createRemainsEntityWidget(HashMap<string,Component*>& componentMap);
    void createRemainsAttributeWidget(HashMap<string,Component*>& componentMap);
};