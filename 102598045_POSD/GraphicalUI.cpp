#include "GraphicalUI.h"
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "ActionData.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QSignalMapper>
#include "ControllerEvent.h"
#include "StateID.h"
#include "State.h"

GraphicalUI::GraphicalUI(GraphicalPresentation* graphicalPresentation): graphicalPresentation(graphicalPresentation),QMainWindow(){
    this->setTitle(ApplicationSetting::Title);
    this->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    this->initialGraphicView();
    this->initialAllAction();
    this->initialMenuBar();
    this->initialToolBar();
    this->initialNotifyMap();
    QMetaObject::connectSlotsByName(this);
    this->graphicalPresentation->registerObserver(this);
    qRegisterMetaType<string>("string");
    connect(this,SIGNAL(notifyEvent(int)),this,SLOT(executeNotify(int)));
    this->switchState(StateID::PointerState);
}

GraphicalUI::~GraphicalUI(){
    this->graphicalPresentation->unregisterObserver(this);
    delete this->fileMenuItem;
    this->refresh();
}

GraphicalPresentation* GraphicalUI::getGraphicalPresentation(){
    return this->graphicalPresentation;
}

void GraphicalUI::notify(int notifiedEventType){
    this->notifyEvent(notifiedEventType);
}

void GraphicalUI::closeEvent(QCloseEvent* closeEvent){
    this->close();
}

void GraphicalUI::keyPressEvent(QKeyEvent* keyEvent){
    if(keyEvent->key() == Key_Control)
        this->graphicalPresentation->keyCtrlPressed();
}

void GraphicalUI::keyReleaseEvent(QKeyEvent* keyEvent){
    if(keyEvent->key() == Key_Control)
        this->graphicalPresentation->keyCtrlReleased();
}

void GraphicalUI::mousePress(){
    this->graphicalPresentation->getState()->mousePressEvent();
}

void GraphicalUI::mouseMove(){
    this->graphicalPresentation->getState()->mouseMoveEvent();
}

void GraphicalUI::mouseRelease(){
    this->graphicalPresentation->getState()->mouseReleaseEvent();
}

void GraphicalUI::setTitle(string title){
    this->setWindowTitle(QString(title.c_str()));
}

void GraphicalUI::initialGraphicView(){
    this->view = new QGraphicsView(this);
    this->scene = new GUIScene(0,0,ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight,this);
    this->view->setScene(this->scene);
    this->setCentralWidget(view);
}

void GraphicalUI::initialAllAction(){
    this->actionMap = new QActionMap(this);
    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    QSignalMapper* signalMapper = new QSignalMapper (this) ;

    QAction* pointerStateAction = this->actionMap->getQAction(ActionData::PointerState);
    connect(pointerStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(pointerStateAction,StateID::PointerState);

    QAction* connectStateAction = this->actionMap->getQAction(ActionData::ConnectState);
    connect(connectStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(connectStateAction,StateID::ConnectState);

    QAction* attributeStateAction = this->actionMap->getQAction(ActionData::AttributeState);
    connect(attributeStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(attributeStateAction,StateID::AttributeState);

    QAction* entityStateAction = this->actionMap->getQAction(ActionData::EntityState);
    connect(entityStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(entityStateAction,StateID::EntityState);

    QAction* relationShipStateAction = this->actionMap->getQAction(ActionData::RelationShipState);
    connect(relationShipStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
    signalMapper->setMapping(relationShipStateAction,StateID::RelationShipState);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(switchState(int))) ;
}

void GraphicalUI::initialMenuBar(){
    this->menuBar = new QMenuBar(this);
    this->fileMenuItem = new FileMenuItem(this->actionMap);
    this->menuBar->addMenu(this->fileMenuItem);
    this->setMenuBar(this->menuBar);
}

void GraphicalUI::initialToolBar(){
    this->fileToolBar = new FileToolBar(this->actionMap,this);
    this->addToolBar(this->fileToolBar);
    this->addDrawableToolBar = new AddDrawableToolBar(this,this->actionMap);
    this->addToolBar(this->addDrawableToolBar);
}

void GraphicalUI::initialNotifyMap(){
    this->notifyMap.put(ControllerEvent::OpenFile,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::AddNode,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::ConnectTwoNodes,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::DisplayDiagram,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::SetPrimaryKey,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::DisplayTable,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::DeleteComponent,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::Undo,&GraphicalUI::displayDiagram);
    this->notifyMap.put(ControllerEvent::Redo,&GraphicalUI::displayDiagram);
}

void GraphicalUI::openFile(){
    QFileDialog* openFileDialog = new QFileDialog(NULL,QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    if(openFileDialog->exec()){
        QString filePath = openFileDialog->selectedFiles().first();
        this->graphicalPresentation->openFile(filePath.toStdString());
    }
    delete openFileDialog;
}

void GraphicalUI::close(){
    this->graphicalPresentation->close();
}

void GraphicalUI::switchState(int stateID){
    this->addDrawableToolBar->selectToolButton(stateID);
    this->graphicalPresentation->switchState(stateID);
}
//execute notify event that are mapped.
void GraphicalUI::executeNotify(int notifiedEventType){
    if(notifyMap.containsKey(notifiedEventType)){
        ViewNotifyFunction notifyFunction = notifyMap.get(notifiedEventType);
        (this->*notifyFunction)();
    }
}

void GraphicalUI::displayDiagram(){
    this->refresh();
    HashMap<string,ComponentWidget*> componentWidgetMap = this->graphicalPresentation->getAllComponentWidgets();
    for each(ComponentWidget* componentWidget in componentWidgetMap)
        this->scene->addItem(componentWidget);
}

void GraphicalUI::refresh(){
    this->scene->clear();
}