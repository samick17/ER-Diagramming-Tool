#include "GraphicalUI.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QSignalMapper>
#include <QInputDialog>
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "ActionData.h"
#include "ControllerEvent.h"
#include "StateID.h"
#include "DialogSetting.h"
#include <iostream>

GraphicalUI::GraphicalUI(GraphicalPresentation* graphicalPresentation): graphicalPresentation(graphicalPresentation),QMainWindow(){
    this->setTitle(ApplicationSetting::Title,ApplicationSetting::IconPath);
    this->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    this->initialGraphicView();
    this->initialAllAction();
    this->initialMenuBar();
    this->initialToolBar();
    this->initialSyncMap();
    QMetaObject::connectSlotsByName(this);
    qRegisterMetaType<string>("string");
    connect(this,SIGNAL(onSyncEvent(string)),this,SLOT(executeSync(string)));
    this->switchState(StateID::PointerState);
    this->graphicalPresentation->registerSynchronizer(this);
}

GraphicalUI::~GraphicalUI(){
    this->graphicalPresentation->unregisterSynchronizer(this);
    delete this->fileMenuItem;
    delete this->addMenuItem;
}

GraphicalPresentation* GraphicalUI::getGraphicalPresentation(){
    return this->graphicalPresentation;
}

void GraphicalUI::sync(string syncEventType){
    this->onSyncEvent(syncEventType);
}

void GraphicalUI::closeEvent(QCloseEvent* closeEvent){
    this->close();
}

void GraphicalUI::keyPressEvent(QKeyEvent* keyEvent){
    this->setKeyCtrlPressed(keyEvent);
}

void GraphicalUI::keyReleaseEvent(QKeyEvent* keyEvent){
    this->setKeyCtrlPressed(keyEvent);
}

void GraphicalUI::setTitle(string title,string iconPath){
    this->setWindowTitle(QString(title.c_str()));
    this->setWindowIcon(QIcon(iconPath.c_str()));
}

void GraphicalUI::initialGraphicView(){
    this->view = new QGraphicsView(this);
    this->scene = new GUIScene(this->view->contentsRect(),this,this->view);
    this->view->setScene(this->scene);
    this->setCentralWidget(view);
}

void GraphicalUI::initialAllAction(){
    this->actionMap = new QActionMap(this);
    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    //use signal mapper to pass state argument
    QSignalMapper* signalMapper = new QSignalMapper(this);
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
    this->fileMenuItem = new FileMenuItem(this->actionMap,this);
    this->addMenuItem = new AddMenuItem(this->actionMap,this);
    this->menuBar->addMenu(this->fileMenuItem);
    this->menuBar->addMenu(this->addMenuItem);
    this->setMenuBar(this->menuBar);
}

void GraphicalUI::initialToolBar(){
    this->fileToolBar = new FileToolBar(this->actionMap,this);
    this->addToolBar(this->fileToolBar);
    this->addDrawableToolBar = new AddDrawableToolBar(this,this->actionMap);
    this->addToolBar(this->addDrawableToolBar);
}

void GraphicalUI::initialSyncMap(){
    this->syncMap.put(ControllerEvent::OpenFile,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::AddNode,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::ConnectTwoNodes,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::DisplayDiagram,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::SetPrimaryKey,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::DisplayTable,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::DeleteComponent,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::Undo,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::Redo,&GraphicalUI::refreshAllWidgets);
    this->syncMap.put(ControllerEvent::Close,&GraphicalUI::close);
}

void GraphicalUI::openFile(){
    QFileDialog* openFileDialog = new QFileDialog(NULL,QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    if(openFileDialog->exec()){
        QString filePath = openFileDialog->selectedFiles().first();
        this->scene->clear();
        this->graphicalPresentation->openFile(filePath.toStdString());
    }
    delete openFileDialog;
}

void GraphicalUI::close(){
    this->graphicalPresentation->close();
}

void GraphicalUI::switchState(int stateID){
    this->graphicalPresentation->switchState(stateID);
    //display input dialog
    if(stateID >= StateID::AttributeState && stateID <= StateID::RelationShipState){
        bool isOK;
        QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal,"",&isOK);
        if(isOK){
            ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
            componentData->setName(text.toStdString());
        }
        else {
            this->graphicalPresentation->switchState(StateID::PointerState);
        }
    }
}
//execute sunchronization event that are mapped.
void GraphicalUI::executeSync(string syncEventType){
    if(this->syncMap.containsKey(syncEventType)){
        ViewSyncFunction syncFunction = this->syncMap.get(syncEventType);
        (this->*syncFunction)();
    }
}

void GraphicalUI::refreshAllWidgets(){
    this->graphicalPresentation->updateAllComponentData();
    this->scene->refreshAllWidgets();
}

void GraphicalUI::setKeyCtrlPressed(QKeyEvent* keyEvent){
    bool isCtrlPressed = keyEvent->key() == Key_Control;
    isCtrlPressed &= keyEvent->type() == QEvent::KeyPress;
    this->graphicalPresentation->setKeyCtrlState(isCtrlPressed);
}