#pragma once

#include "Component.h"
#include <set>
#include "Presentation.h"
#include "Subject.h"

class ComponentData;
class StateSubject;

class GraphicalPresentation : public Subject{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,Component*> getAllComponents();
    set<ComponentData*> getAllComponentDataSet();
    void updateAllComponentData();
    Node* getLastAddedNode();
    Component* getLastPressedComponent();
    Component* getLastReleasedComponent();

    void addNode(string nodeType,string nodeName,Point position);
    void addConnection(Component* sourceComponent,Component* targetComponent);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isWidgetSelected(string componentID);
    void selectWidget();
    void selectLastPressedWidget();
    void revertSelectWidget(bool isSelected,string componentID);
    void moveSelectedWidget(Point position);
    void unSelectAll();
    void switchState(int stateID);
    void setKeyCtrlState(bool isCtrlPressed);
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);

    void mousePressEvent(Point position,ComponentData* componentData);
    void mouseMoveEvent(Point position,ComponentData* componentData);
    void mouseReleaseEvent(Point position,ComponentData* componentData);
protected:
    //observer
    void doRegisterObserver(IObserver* observer);
    void doUngisterObserver(IObserver* observer);
private:
    Presentation* presentation;
    set<string> selectedWidgetSet;
    set<ComponentData*> componentDataSet;
    ComponentData* componentDataForPreview;
    bool isCtrlPressed;
    StateSubject* stateSubject;
    Node* lastAddedNode;
    Component* lastPressedComponent;
    Component* lastReleasedComponent;
};