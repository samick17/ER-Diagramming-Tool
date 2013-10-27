#include "FileMenuItem.h"
#include "Presentation.h"
#include "GraphicalUI.h"

FileMenuItem::FileMenuItem(GraphicalUI* graphicalUI){
	this->setTitle(QString("File"));
	
	QAction* openFileAction = new QAction(QIcon(":/res/Resources/open.png"),"&Open...",this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));
	connect(openFileAction, SIGNAL(triggered()), graphicalUI, SLOT(openFile()));

	QAction* exitAction = new QAction(QIcon(":/res/Resources/exit.png"),"&Exit",this);	
	exitAction->setShortcut(QKeySequence("Alt+F4"));
	connect(exitAction, SIGNAL(triggered()), graphicalUI, SLOT(close()));

	this->addAction(openFileAction);
	this->addAction(exitAction);
}

FileMenuItem::~FileMenuItem(){
}