#pragma once

#include "Component.h"
#include "Presentation.h"
#include <QPointF>
#include <set>
#include "Subject.h"
#include "IObserver.h"

class State;
class StateSubject;

class GraphicalPresentation : public Subject,public IObserver{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    State* getState();
    StateSubject* getStateSubject();
    HashMap<string,Component*>& getAllComponents();

    void addNode(string nodeType,string nodeName,QPointF position);
    void openFile(string filePath);
    void saveFile(string filePath);
    void close();
    bool isSelected(string componentID);
    void selectWidget(string componentID);
    void switchState(int stateID);
    void keyCtrlPressed();
    void keyCtrlReleased();
    //synchronize view
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);

    void notify(ISubject* subject);
protected:
    //observer
    void doRegisterObserver(IObserver* observer);
    void doUngisterObserver(IObserver* observer);
private:
    Presentation* presentation;
    set<string> selectedWidgetSet;
    bool isCtrlPressed;
    StateSubject* stateSubject;
};