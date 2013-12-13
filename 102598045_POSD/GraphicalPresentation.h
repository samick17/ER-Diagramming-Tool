#pragma once

#include "Component.h"
#include "HashMap.h"
#include "Presentation.h"
#include "StateSubject.h"

class Connector;

class GraphicalPresentation{
    friend class GraphicalPresentation;
    FRIEND_TEST(GraphicalPresentationTest,testDeleteComponentDataForPreview);
    FRIEND_TEST(GraphicalPresentationTest,testUpdateAllComponentData);
    FRIEND_TEST(GraphicalPresentationTest,testAddNode);
    FRIEND_TEST(GraphicalPresentationTest,testAddConnection);
    FRIEND_TEST(GraphicalPresentationTest,testOpenFile);
    FRIEND_TEST(GraphicalPresentationTest,testIsWidgetSelected);
    FRIEND_TEST(GraphicalPresentationTest,testSelectWidget);
    FRIEND_TEST(GraphicalPresentationTest,testSelectLastPressedWidget);
    FRIEND_TEST(GraphicalPresentationTest,testMoveSelectedWidget);
    FRIEND_TEST(GraphicalPresentationTest,testUnSelectAll);
    FRIEND_TEST(GraphicalPresentationTest,testGetComponentByComponentData);
    FRIEND_TEST(GraphicalPresentationTest,testNeedToSetCardinality);
    FRIEND_TEST(GraphicalPresentationTest,testSetCardinality);
    friend class ConnectStateTest;
    FRIEND_TEST(ConnectStateTest,testDoMousePressEvent);
    FRIEND_TEST(ConnectStateTest,testDoMouseDragEvent);
    friend class SetPrimaryKeyStateTest;
    FRIEND_TEST(SetPrimaryKeyStateTest,testDoMousePressEvent);
    friend class PointerStateTest;
    FRIEND_TEST(PointerStateTest,testDoMousePressEvent);
    FRIEND_TEST(PointerStateTest,testDoMouseDragEvent);
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,ComponentData*> getAllComponentDataMap();
    ComponentData* getComponentDataForPreview();
    void setComponentDataForPreview(ComponentData* componentDataForPreview);

    void updateAllComponentData();
    Component* getLastPressedComponent();
    Component* getLastMovedComponent();
    Component* getLastReleasedComponent();

    void addNode(string nodeType,string nodeName,Point centerPosition);
    void addConnection(Component* sourceComponent,Component* targetComponent);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool canUndo();
    bool canRedo();
    void undo();
    void redo();
    void setPrimaryKey(string componentID);
    void setComponentText(string componentID,string text);
    bool isSelectAnyWidgets();
    void deleteComponent();
    bool isWidgetSelected(string componentID);
    void selectWidget();
    void selectLastPressedWidget();
    void previewMoveSelectedWidget(Point deltaPosition);
    void moveSelectedWidget(Point mousePressPosition,Point mouseReleasePosition);
    void unSelectAll();
    void switchState(int stateID);
    void setKeyCtrlState(bool isCtrlPressed);
    //cardinality
    bool needToSetCardinality();
    bool setCardinality(string cardinality);
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);
    //observer pattern
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);

    void mousePressEvent(Point position,ComponentData* componentData);
    void mouseMoveEvent(Point position,ComponentData* componentData);
    void mouseReleaseEvent(Point position,ComponentData* componentData);
private:
    Component* getComponentByComponentData(ComponentData* componentData);
    void deleteComponentDataForPreview();
    Presentation* presentation;
    vector<string> selectedWidgetVector;
    HashMap<string,ComponentData*> componentDataMap;
    ComponentData* componentDataForPreview;
    bool isCtrlPressed;
    StateSubject stateSubject;
    Connector* lastAddedConnector;
    Component* lastPressedComponent;
    Component* lastMovedComponent;
    Component* lastReleasedComponent;
};