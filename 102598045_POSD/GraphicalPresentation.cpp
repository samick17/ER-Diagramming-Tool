#include "GraphicalPresentation.h"
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "WidgetDefaultSetting.h"
#include "Number.h"
#include "ControllerEvent.h"
#include "ERModelUtil.h"
#include "StateFactory.h"
#include "StateID.h"
#include "StateSubject.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
    this->isCtrlPressed = false;
    this->stateSubject = new StateSubject();
    this->presentation->registerObserver(this);
}

GraphicalPresentation::~GraphicalPresentation(){
    delete this->stateSubject;
    this->presentation->unregisterObserver(this);
}

State* GraphicalPresentation::getState(){
    return this->stateSubject->getState();
}

StateSubject* GraphicalPresentation::getStateSubject(){
    return this->stateSubject;
}

HashMap<string,Component*>& GraphicalPresentation::getAllComponents(){
    return this->presentation->getAllComponents();
}

void GraphicalPresentation::addNode(string nodeType,string nodeName,QPointF position){
    Node* node = this->presentation->addNode(nodeType);
    node->setName(nodeName);
    Size size = Size::DefaultSize();
    node->setPosition(Point(position.x()-size.getWidth()/Number::Two,position.y()-size.getHeight()/Number::Two));
    node->setSize(size);
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::openFile(string filePath){
    this->presentation->openFile(filePath);
    this->presentation->sync(ControllerEvent::DisplayDiagram);
}

void GraphicalPresentation::saveFile(string filePath){
    this->presentation->saveFile(filePath);
}
//close & exit application
void GraphicalPresentation::close(){
    this->presentation->close();
}
//is widget being selected?
bool GraphicalPresentation::isSelected(string componentID){
    if(this->selectedWidgetSet.find(componentID) != this->selectedWidgetSet.end())
        return true;
    return false;
}
//select widget : highlight/unhilight selected,notify all
void GraphicalPresentation::selectWidget(string componentID){
    bool isSelected = this->isSelected(componentID);
    if(this->isCtrlPressed){
        if(this->isSelected(componentID)){
            this->selectedWidgetSet.erase(componentID);
        }else {
            this->selectedWidgetSet.insert(componentID);
        }
    }else {
        this->selectedWidgetSet.clear();
        if(isSelected){
            this->selectedWidgetSet.erase(componentID);
        }else {
            this->selectedWidgetSet.insert(componentID);
        }
    }
    this->Subject::notify();
}

void GraphicalPresentation::switchState(int stateID){
    this->stateSubject->switchState(stateID,this);
}
//key pressed
void GraphicalPresentation::keyCtrlPressed(){
    this->isCtrlPressed = true;
}

void GraphicalPresentation::keyCtrlReleased(){
    this->isCtrlPressed = false;
}
//synchronized view
void GraphicalPresentation::registerSynchronizer(ISynchronizer* synchronizer){
    this->presentation->registerSynchronizer(synchronizer);
}

void GraphicalPresentation::unregisterSynchronizer(ISynchronizer* synchronizer){
    this->presentation->unregisterSynchronizer(synchronizer);
}

void GraphicalPresentation::sync(int syncEventType){
    this->presentation->sync(syncEventType);
}

void GraphicalPresentation::doRegisterObserver(IObserver* observer){
    this->presentation->registerObserver(observer);
}

void GraphicalPresentation::doUngisterObserver(IObserver* observer){
    this->presentation->unregisterObserver(observer);
}

void GraphicalPresentation::notify(ISubject* subject){
}