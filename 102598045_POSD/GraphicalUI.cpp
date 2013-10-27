#include "GraphicalUI.h"
#include "Presentation.h"
#include "ApplicationSetting.h"
#include <QFileDialog>

GraphicalUI::GraphicalUI(Presentation* presentation): presentation(presentation),QMainWindow(){
	setTitle();	
	fileMenuItem = new FileMenuItem(this);
	this->initialMenuBar();
	this->initialToolBar();
	this->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    QMetaObject::connectSlotsByName(this);
}

GraphicalUI::~GraphicalUI(){
	delete this->fileMenuItem;
}

Presentation* GraphicalUI::getPresentation(){
	return this->presentation;
}

void GraphicalUI::setTitle(){
	QString title = QString(ApplicationSetting::Title.c_str());
	this->setWindowTitle(title);
}

void GraphicalUI::initialMenuBar(){
	this->menuBar.addMenu(this->fileMenuItem);
	this->setMenuBar(&this->menuBar);
}

void GraphicalUI::initialToolBar(){
	QAction* openFileAction = new QAction(QIcon(":/res/Resources/open.png"),"&Open...",this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));
	this->toolBar.connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

	QAction* exitAction = new QAction(QIcon(":/res/Resources/exit.png"),"&Exit...",this);
    exitAction->setShortcut(QKeySequence("Alt+F4"));
	this->toolBar.connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	this->toolBar.addAction(openFileAction);
	this->toolBar.addAction(exitAction);
	this->addToolBar(&this->toolBar);
}

void GraphicalUI::openFile(){
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.erd)"));
	if(!fileName.isEmpty()){		
		this->presentation->openFile(fileName.toStdString());
	}
}

void GraphicalUI::close(){
	this->presentation->close();
}