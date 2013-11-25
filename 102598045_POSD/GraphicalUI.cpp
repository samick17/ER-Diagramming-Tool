#include "GraphicalUI.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QSignalMapper>
#include <QInputDialog>
#include <QHBoxLayout>
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "ActionData.h"
#include "ControllerEvent.h"
#include "StateID.h"
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
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    this->view = new QGraphicsView(this);
    this->scene = new GUIScene(this);
    this->view->setScene(this->scene);
    this->view->setMouseTracking(true);
    layout->addWidget(this->view);
    layout->setStretchFactor(this->view,COMPONENT_VIEW_STRETCH);

    this->tableView = new GUITableView(this->graphicalPresentation);
    layout->addWidget(this->tableView);
    layout->setStretchFactor(this->tableView,TABLE_VIEW_STRETCH);
}

void GraphicalUI::initialAllAction(){
    this->actionMap = new QActionMap(this);
    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    QAction* undoAction = this->actionMap->getQAction(ActionData::Undo);
    connect(undoAction,SIGNAL(triggered()),this,SLOT(undo()));
    QAction* redoAction = this->actionMap->getQAction(ActionData::Redo);
    connect(redoAction,SIGNAL(triggered()),this,SLOT(redo()));
    QAction* deleteComponentAction = this->actionMap->getQAction(ActionData::Delete);
    connect(deleteComponentAction,SIGNAL(triggered()),this,SLOT(deleteComponent()));
    
    //Set State Action : use signal mapper to pass state argument
    QSignalMapper* signalMapper = new QSignalMapper(this);
    int stateID = StateID::PointerState;
    for(unsigned int index = ActionData::PointerState;index <= ActionData::SetPrimaryKeyState;index++){
        QAction* pointerStateAction = this->actionMap->getQAction(index);
        connect(pointerStateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
        if(stateID >= StateID::AddAttributeState && stateID <= StateID::AddRelationShipState)
            connect(pointerStateAction,SIGNAL(triggered()),this,SLOT(displaySetTextDialog()));
        signalMapper->setMapping(pointerStateAction,stateID);
        stateID++;
    }
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
    QFileDialog* openFileDialog = new QFileDialog(NULL,QString(ActionData::ActionName[ActionData::OpenFile].c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
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

void GraphicalUI::undo(){
    this->graphicalPresentation->undo();
}

void GraphicalUI::redo(){
    this->graphicalPresentation->redo();
}

void GraphicalUI::deleteComponent(){
    this->graphicalPresentation->deleteComponent();
}

void GraphicalUI::switchState(int stateID){
    this->graphicalPresentation->switchState(stateID);
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
    this->graphicalPresentation->notify();
}

void GraphicalUI::setKeyCtrlPressed(QKeyEvent* keyEvent){
    bool isCtrlPressed = keyEvent->key() == Key_Control;
    isCtrlPressed &= keyEvent->type() == QEvent::KeyPress;
    this->graphicalPresentation->setKeyCtrlState(isCtrlPressed);
}

void GraphicalUI::displaySetTextDialog(){
    bool isOKClicked;
    QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal,StringSymbol::Empty.c_str(),&isOKClicked);
    if(isOKClicked){
        ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
        componentData->setName(text.toStdString());
        this->graphicalPresentation->notify();
    }
    else {
        this->graphicalPresentation->switchState(StateID::PointerState);
    }
}