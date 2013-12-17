#pragma once

#include "Component.h"
#include "HashMap.h"
#include "Presentation.h"
#include "StateSubject.h"

class Connector;

class GraphicalPresentation : public Subject{
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
    HashMap<string,Table*> getAllTables();
    ComponentData* getComponentDataForPreview();
    void setComponentDataForPreview(ComponentData* componentDataForPreview);

    void updateAllComponentData();
    Component* getLastPressedComponent();
    Component* getLastMovedComponent();
    Component* getLastReleasedComponent();
    bool getIsDisplayDBTable();

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
    //is some funtionality available
    bool isSelectAnyWidgets();
    bool canPasteWidgets();
    bool canUndo();
    bool canRedo();

    bool isWidgetSelected(string componentID);
    void selectWidget();
    void selectLastPressedWidget();
    void previewMoveSelectedWidget(Point deltaPosition);
    void moveSelectedWidget(Point mousePressPosition,Point mouseReleasePosition);
    void unSelectAll();
    void switchState(int stateID);
    void switchDisplayDBTable();
    void setKeyCtrlState(bool isCtrlPressed);
    //cardinality
    bool needToSetCardinality();
    bool setCardinality(string cardinality);
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);
    //observer pattern-delegate to presentation
    void registerObserverToModel(IObserver* observer);
    void unregisterObserverToModel(IObserver* observer);
    void notifyModel();

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
    bool isDisplayDBTable;
    StateSubject stateSubject;
    Connector* lastAddedConnector;
    Component* lastPressedComponent;
    Component* lastMovedComponent;
    Component* lastReleasedComponent;
};