#include "FileMenuItem.h"
#include "Presentation.h"
#include "GraphicalUI.h"

FileMenuItem::FileMenuItem(GraphicalUI* graphicalUI){
	this->setTitle(QString("File"));
	
	this->openFileAction = new QAction("&Open...",this);
    this->openFileAction->setShortcut(tr("Ctrl+O"));
	connect(openFileAction, SIGNAL(triggered()), graphicalUI, SLOT(openFile()));

	this->exitAction = new QAction("&Exit",this);	
	this->exitAction->setShortcut(tr("Alt+F4"));
	connect(exitAction, SIGNAL(triggered()), graphicalUI->getPresentation(), SLOT(close()));

	this->addAction(this->openFileAction);
	this->addAction(this->exitAction);
}

FileMenuItem::~FileMenuItem(){
}