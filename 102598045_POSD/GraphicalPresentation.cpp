#include "GraphicalPresentation.h"
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "WidgetDefaultSetting.h"
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

StateSubject* GraphicalPresentation::getStateSubject(){
    return this->stateSubject;
}

HashMap<string,Component*>& GraphicalPresentation::getAllComponents(){
    return this->presentation->getAllComponents();
}

void GraphicalPresentation::setText(string text){
    if(text.empty())
        this->switchState(StateID::PointerState);
    else
        this->text = text;
}

string GraphicalPresentation::getText(){
    return this->text;
}

Node* GraphicalPresentation::getLastAddedNode(){
    return this->lastAddedNode;
}

Component* GraphicalPresentation::getLastPressedComponent(){
	return this->lastPressedComponent;
}

Component* GraphicalPresentation::getLastMovedComponent(){
	return this->lastMovedComponent;
}

Component* GraphicalPresentation::getLastReleasedComponent(){
	return this->lastReleasedComponent;
}

void GraphicalPresentation::addNode(string nodeType,string nodeName,Point position){
    Node* node = this->presentation->addNode(nodeType);
    this->lastAddedNode = node;
    node->setName(nodeName);
    node->setSize(Size::DefaultSize());
    node->setCenterPosition(position);
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
void GraphicalPresentation::selectWidget(){
	if(this->lastPressedComponent == NULL){
		this->unSelectAll();
		return;
	}
    string componentID = this->lastPressedComponent->getID();
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

void GraphicalPresentation::moveSelectedWidget(Point deltaPosition){
    HashMap<string,Component*> componentMap = this->presentation->getAllComponents();
    for each(string componentID in this->selectedWidgetSet){
        Component* component = componentMap.get(componentID);
        Point position = component->getRect().getPosition();
		component->setPosition(position+deltaPosition);
    }
}

void GraphicalPresentation::unSelectAll(){
    this->selectedWidgetSet.clear();
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

void GraphicalPresentation::mousePressEvent(Point position,Component* component){
	this->lastPressedComponent = component;
    this->stateSubject->getState()->mousePressEvent(position);
}

void GraphicalPresentation::mouseMoveEvent(Point position,Component* component){
	this->lastMovedComponent = component;
    this->stateSubject->getState()->mouseMoveEvent(position);
}

void GraphicalPresentation::mouseReleaseEvent(Point position,Component* component){
	this->lastReleasedComponent = component;
    this->stateSubject->getState()->mouseReleaseEvent(position);
}