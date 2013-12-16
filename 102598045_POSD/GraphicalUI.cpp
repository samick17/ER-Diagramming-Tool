#include "GraphicalUI.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QSignalMapper>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QMenuBar>
#include "FileMenuItem.h"
#include "AddMenuItem.h"
#include "EditMenuItem.h"
#include "HelpMenuItem.h"
#include "FileToolBar.h"
#include "EditToolBar.h"
#include "AddDrawableToolBar.h"
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
    this->graphicalPresentation->notify();
}

GraphicalUI::~GraphicalUI(){
    this->graphicalPresentation->unregisterSynchronizer(this);
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
    QHBoxLayout* horizontalBoxLayout = new QHBoxLayout();
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(horizontalBoxLayout);
    this->setCentralWidget(centralWidget);
    //initial left part view
    this->scene = new GUIScene(this);
    this->view = new QGraphicsView(this->scene,this);
    this->view->setMouseTracking(true);
    horizontalBoxLayout->addWidget(this->view);
    horizontalBoxLayout->setStretchFactor(this->view,COMPONENT_VIEW_STRETCH);
    //initial right part view
    this->tableView = new GUITableView(this->graphicalPresentation);
    horizontalBoxLayout->addWidget(this->tableView);
    horizontalBoxLayout->setStretchFactor(this->tableView,TABLE_VIEW_STRETCH);
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
        QAction* stateAction = this->actionMap->getQAction(index);
        connect(stateAction,SIGNAL(triggered()),signalMapper,SLOT(map()));
        if(stateID >= StateID::AddAttributeState && stateID <= StateID::AddRelationShipState)
            connect(stateAction,SIGNAL(triggered()),this,SLOT(displayEditTextDialog()));
        signalMapper->setMapping(stateAction,stateID);
        stateID++;
    }
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(switchState(int))) ;

    QAction* copyAction = this->actionMap->getQAction(ActionData::Copy);
    connect(copyAction,SIGNAL(triggered()),this,SLOT(copyComponents()));
    QAction* pasteAction = this->actionMap->getQAction(ActionData::Paste);
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(pasteComponents()));
    QAction* cutAction = this->actionMap->getQAction(ActionData::Cut);
    connect(cutAction,SIGNAL(triggered()),this,SLOT(cutComponents()));
    QAction* aboutAction = this->actionMap->getQAction(ActionData::About);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(displayAbout()));
}

void GraphicalUI::initialMenuBar(){
    QMenuBar* menuBar = new QMenuBar(this);
    menuBar->addMenu(new FileMenuItem(this->actionMap,this));
    menuBar->addMenu(new AddMenuItem(this->actionMap,this));
    menuBar->addMenu(new EditMenuItem(this->actionMap,this));
    menuBar->addMenu(new HelpMenuItem(this->actionMap,this));
    this->setMenuBar(menuBar);
}

void GraphicalUI::initialToolBar(){
    this->addToolBar(new FileToolBar(this,this->actionMap));
    this->addToolBar(new EditToolBar(this,this->actionMap));
    this->addToolBar(new AddDrawableToolBar(this,this->actionMap));
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
    bool isCtrlKey = (keyEvent->key() == Key_Control);
    bool isKeyPressed = keyEvent->type() == QEvent::KeyPress;

    bool isCtrlKeyPressed = isCtrlKey && isKeyPressed;
    this->graphicalPresentation->setKeyCtrlState(isCtrlKeyPressed);
}

void GraphicalUI::displayEditTextDialog(){
    bool isOKClicked;
    QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal,StringSymbol::Empty.c_str(),&isOKClicked);
    if(isOKClicked){
        ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
        componentData->setName(text.toStdString());
        this->graphicalPresentation->notify();
    }
    else{
        this->graphicalPresentation->setComponentDataForPreview(NULL);
        this->graphicalPresentation->switchState(StateID::PointerState);
    }
}

void GraphicalUI::copyComponents(){
}

void GraphicalUI::pasteComponents(){
}

void GraphicalUI::cutComponents(){
}

void GraphicalUI::displayAbout(){
}