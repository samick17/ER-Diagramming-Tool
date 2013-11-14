#pragma once

#include "Component.h"
#include "Presentation.h"
#include <set>
#include "Subject.h"
#include "IObserver.h"

class State;
class StateSubject;

class GraphicalPresentation : public Subject,public IObserver{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    StateSubject* getStateSubject();
    HashMap<string,Component*>& getAllComponents();
    void setText(string text);
    string getText();

    void addNode(string nodeType,string nodeName,Point position);
    Node* getLastAddedNode();
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(string componentID);
    void selectWidget(string componentID);
    void unSelectAll();
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);

    void notify(ISubject* subject);

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
    Node* lastNode;
};