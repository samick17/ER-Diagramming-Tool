#include "GraphicalUI.h"
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "ActionData.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QSignalMapper>
#include "ControllerEvent.h"
#include "StateID.h"
#include <QInputDialog>
#include "DialogSetting.h"

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
    connect(this,SIGNAL(syncEvent(int)),this,SLOT(executeSync(int)));
    connect(this,SIGNAL(switchStateEvent(int)),this,SLOT(executeSwitchState(int)));
    this->switchState(StateID::PointerState);
    this->graphicalPresentation->registerSynchronizer(this);
}

GraphicalUI::~GraphicalUI(){
    this->graphicalPresentation->unregisterSynchronizer(this);
    delete this->fileMenuItem;
}

GraphicalPresentation* GraphicalUI::getGraphicalPresentation(){
    return this->graphicalPresentation;
}

GUIScene* GraphicalUI::getScene(){
    return this->scene;
}

void GraphicalUI::sync(int syncEventType){
    this->syncEvent(syncEventType);
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

void GraphicalUI::setTitle(string title,string iconPath){
    this->setWindowTitle(QString(title.c_str()));
    this->setWindowIcon(QIcon(iconPath.c_str()));
}

void GraphicalUI::initialGraphicView(){
    this->scene = new GUIScene(0,0,ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight,this);
    this->view = new QGraphicsView(this);
    this->view->setScene(this->scene);
    this->setCentralWidget(view);
    //this->view->setInteractive(true);
}

void GraphicalUI::initialAllAction(){
    this->actionMap = new QActionMap(this);
    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

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

void GraphicalUI::initialSyncMap(){
    this->syncMap.put(ControllerEvent::OpenFile,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::AddNode,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::ConnectTwoNodes,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::DisplayDiagram,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::SetPrimaryKey,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::DisplayTable,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::DeleteComponent,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::Undo,&GraphicalUI::displayDiagram);
    this->syncMap.put(ControllerEvent::Redo,&GraphicalUI::displayDiagram);
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
    this->switchStateEvent(stateID);
}
//execute notify event that are mapped.
void GraphicalUI::executeSync(int notifiedEventType){
    if(this->syncMap.containsKey(notifiedEventType)){
        ViewSyncFunction syncFunction = this->syncMap.get(notifiedEventType);
        (this->*syncFunction)();
    }
}

void GraphicalUI::executeSwitchState(int stateID){
    if(stateID >= StateID::AttributeState && stateID <= StateID::RelationShipState){
        QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal);
        this->graphicalPresentation->setText(text.toStdString());
    }
}

void GraphicalUI::displayDiagram(){
    this->scene->displayDiagram();
}