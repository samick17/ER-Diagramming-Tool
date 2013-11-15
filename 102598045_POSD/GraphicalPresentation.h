#pragma once

#include "Component.h"
#include "Presentation.h"
#include <set>
#include "Subject.h"

class State;
class StateSubject;

class GraphicalPresentation : public Subject{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,Component*>& getAllComponents();
    void setText(string text);
    string getText();
    Node* getLastAddedNode();
    Component* getLastPressedComponent();
    Component* getLastMovedComponent();
    Component* getLastReleasedComponent();

    void addNode(string nodeType,string nodeName,Point position);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(string componentID);
    void selectWidget();
    void moveSelectedWidget(Point position);
    void unSelectAll();
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);

    void mousePressEvent(Point position,Component* component);
    void mouseMoveEvent(Point position,Component* component);
    void mouseReleaseEvent(Point position,Component* component);
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
    Component* lastMovedComponent;
    Component* lastReleasedComponent;
};