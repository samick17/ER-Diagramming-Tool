#include "GraphicalUI.h"
#include "GraphicalPresentation.h"
#include "ApplicationSetting.h"
#include "Entity.h"
#include <QPainter>
#include <QFileDialog>
#include <QLayout>
#include <EntityWidget.h>

GraphicalUI::GraphicalUI(GraphicalPresentation* graphicalPresentation): graphicalPresentation(graphicalPresentation),QMainWindow(){
    setTitle();    
    fileMenuItem = new FileMenuItem(this);
    this->initialMenuBar();
    this->initialToolBar();
    this->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    this->view = new QGraphicsView(this);
    this->scene = new QGraphicsScene(0,0,ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight,this);
    view->setScene(this->scene);
    this->setCentralWidget(view);
    QMetaObject::connectSlotsByName(this);
    this->scene->addItem(new EntityWidget(new Entity(ComponentData("1","Engineer"))));
}

GraphicalUI::~GraphicalUI(){
    delete this->fileMenuItem;
}

GraphicalPresentation* GraphicalUI::getGraphicalPresentation(){
    return this->graphicalPresentation;
}

void GraphicalUI::setTitle(){
    QString title = QString(ApplicationSetting::Title.c_str());
    this->setWindowTitle(title);
}

void GraphicalUI::initialMenuBar(){
    this->menuBar = new QMenuBar(this);    
    this->menuBar->addMenu(this->fileMenuItem);
    this->setMenuBar(this->menuBar);
}

void GraphicalUI::initialToolBar(){
    this->toolBar = new QToolBar(this);
    this->toolBar->setMovable(false);
    QAction* openFileAction = new QAction(QIcon(":/res/Resources/open.png"),"&Open...",this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));
    this->toolBar->connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    QAction* exitAction = new QAction(QIcon(":/res/Resources/exit.png"),"&Exit...",this);
    exitAction->setShortcut(QKeySequence("Alt+F4"));
    this->toolBar->connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    this->toolBar->addAction(openFileAction);
    this->toolBar->addAction(exitAction);    
    this->addToolBar(this->toolBar);
}


void GraphicalUI::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),tr("C:\\"),tr("Files (*.erd)"));
    if(!fileName.isEmpty()){
		this->graphicalPresentation->openFile(fileName.toStdString());
    }
    displayComponents();
}

void GraphicalUI::close(){
	this->graphicalPresentation->close();
}

void GraphicalUI::displayComponents(){
    
}