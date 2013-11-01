#include "GraphicalUI.h"
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "Entity.h"
#include "ActionData.h"
#include "RelationShipWidget.h"
#include "EntityWidget.h"
#include "AttributeWidget.h"

GraphicalUI::GraphicalUI(GraphicalPresentation* graphicalPresentation): graphicalPresentation(graphicalPresentation),QMainWindow(){
    this->setTitle(ApplicationSetting::Title);
    this->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    this->initialGraphicView();
    this->initialAllAction();
    this->initialMenuBar();
    this->initialToolBar();
    QMetaObject::connectSlotsByName(this);
}

GraphicalUI::~GraphicalUI(){
    delete this->fileMenuItem;
    this->refresh();
}

GraphicalPresentation* GraphicalUI::getGraphicalPresentation(){
    return this->graphicalPresentation;
}

void GraphicalUI::closeEvent(QCloseEvent* closeEvent){
    this->close();
}

void GraphicalUI::setTitle(string title){
    this->setWindowTitle(QString(title.c_str()));
}

void GraphicalUI::initialGraphicView(){
    this->view = new QGraphicsView(this);
    this->scene = new QGraphicsScene(0,0,ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight,this);
    this->view->setScene(this->scene);
    this->setCentralWidget(view);
}

void GraphicalUI::initialAllAction(){
    this->actionMap = new QActionMap(this);
    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    this->toolBar->connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);
    this->toolBar->connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void GraphicalUI::initialMenuBar(){
    this->menuBar = new QMenuBar(this);
    this->fileMenuItem = new FileMenuItem(this->actionMap);
    this->menuBar->addMenu(this->fileMenuItem);
    this->setMenuBar(this->menuBar);
}

void GraphicalUI::initialToolBar(){
    this->toolBar = new QToolBar(this);
    this->toolBar->setMovable(false);

    QAction* openFileAction = this->actionMap->getQAction(ActionData::OpenFile);
    QAction* exitAction = this->actionMap->getQAction(ActionData::Exit);

    this->toolBar->addAction(openFileAction);
    this->toolBar->addAction(exitAction);
    this->addToolBar(this->toolBar);
}

void GraphicalUI::openFile(){
    this->graphicalPresentation->openFile();
    displayComponents();
}

void GraphicalUI::close(){
    this->graphicalPresentation->close();
}

void GraphicalUI::displayComponents(){
    this->refresh();

    for each(Entity* entity in this->graphicalPresentation->getAllEntities()){
    }
    for each(RelationShip* relationShip in this->graphicalPresentation->getAllRelationShips()){
    }
    for each(Attribute* attribute in this->graphicalPresentation->getAllAttributes()){
    }
    for each(Connector* connector in this->graphicalPresentation->getAllConnectors()){
    }
}

void GraphicalUI::refresh(){
    for each(QGraphicsItem* gItem in this->scene->items())
        delete gItem;
    this->scene->clear();
}