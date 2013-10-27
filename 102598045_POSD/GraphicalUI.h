#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include "FileMenuItem.h"

class Presentation;

using namespace Qt;

class GraphicalUI : public QMainWindow{
	Q_OBJECT
public slots:
	void openFile();
	void close();
public:
	GraphicalUI(Presentation* presentation);
	~GraphicalUI();

	void initialGUILayout();
	Presentation* getPresentation();	
private:
	Presentation* presentation;
	FileMenuItem* fileMenuItem;
	QMenuBar menuBar;
	QToolBar toolBar;
	void setTitle();
	void initialMenuBar();
	void initialToolBar();
};
