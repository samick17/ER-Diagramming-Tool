#pragma once

#include "Component.h"
#include "HashMap.h"
#include "Presentation.h"
#include "StateSubject.h"

class GraphicalPresentation : public Subject{
    friend class GraphicalPresentation;
    FRIEND_TEST(GraphicalPresentationTest,testDeleteComponentDataForPreview);
    FRIEND_TEST(GraphicalPresentationTest,testUpdateAllComponentData);
    FRIEND_TEST(GraphicalPresentationTest,testAddNode);
    FRIEND_TEST(GraphicalPresentationTest,testAddConnection);
    FRIEND_TEST(GraphicalPresentationTest,testIsWidgetSelected);
    FRIEND_TEST(GraphicalPresentationTest,testSelectWidget);
    FRIEND_TEST(GraphicalPresentationTest,testSelectLastPressedWidget);
    FRIEND_TEST(GraphicalPresentationTest,testMoveSelectedWidget);
    FRIEND_TEST(GraphicalPresentationTest,testUnSelectAll);
    FRIEND_TEST(GraphicalPresentationTest,testSwitchState);
    FRIEND_TEST(GraphicalPresentationTest,getComponentByComponentData);
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,ComponentData*> getAllComponentDataMap();
    ComponentData* getComponentDataForPreview();
    void setComponentDataForPreview(ComponentData* componentDataForPreview);

    void updateAllComponentData();
    Node* getLastAddedNode();
    Component* getLastPressedComponent();
    Component* getLastMovedComponent();
    Component* getLastReleasedComponent();

    void addNode(string nodeType,string nodeName,Point centerPosition);
    void addConnection(Component* sourceComponent,Component* targetComponent);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    void undo();
    void redo();
    void setPrimaryKey(string componentID);
    void setComponentText(string componentID,string text);
    void deleteComponent();
    bool isWidgetSelected(string componentID);
    void selectWidget();
    void selectLastPressedWidget();
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
    void doUnregisterObserver(IObserver* observer);
private:
    Component* getComponentByComponentData(ComponentData* componentData);
    void deleteComponentDataForPreview();
    Presentation* presentation;
    vector<string> selectedWidgetVector;
    HashMap<string,ComponentData*> componentDataMap;
    ComponentData* componentDataForPreview;
    bool isCtrlPressed;
    StateSubject stateSubject;
    Node* lastAddedNode;
    Component* lastPressedComponent;
    Component* lastMovedComponent;
    Component* lastReleasedComponent;
};