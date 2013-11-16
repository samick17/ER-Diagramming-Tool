#pragma once

#include "Component.h"
#include <set>
#include "Presentation.h"
#include "Subject.h"

class StateSubject;

class GraphicalPresentation : public Subject{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,Component*> getAllComponents();
    void setText(string text);
    string getText();
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
    void revertSelectWidget(bool isSelected,string componentID);
    void moveSelectedWidget(Point position);
    void unSelectAll();
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);

    void mousePressEvent(Point position,Component* component);
    void mouseMoveEvent(Point position,Component* component);
    void mouseReleaseEvent(Point position,Component* component);
    //preview connector
    void setPreviewState(bool showPreview);
    bool getPreviewState();
    void setPreviewSourcePoint(Point sourcePoint);
    Point getPreviewSourcePoint();
    void setPreviewTargetPoint(Point currentPoint);
    Point getPreviewTargetPoint();
protected:
    //observer
    void doRegisterObserver(IObserver* observer);
    void doUngisterObserver(IObserver* observer);
private:
    Presentation* presentation;
    set<string> selectedWidgetSet;
    bool isCtrlPressed;
    StateSubject* stateSubject;
    string text;
    Node* lastAddedNode;
    Component* lastPressedComponent;
    Component* lastReleasedComponent;
    bool showPreview;
    Point sourcePoint;
    Point currentPoint;
};