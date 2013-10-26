#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include "GUILayout.h"

class Presentation;

using namespace Qt;

class GraphicalUI : public QMainWindow{
	Q_OBJECT
public slots:
	void openFile();
public:
	GraphicalUI(Presentation* presentation,QWidget *parent = 0, WFlags flags = 0);
	~GraphicalUI();

	Presentation* getPresentation();	
private:
	Presentation* presentation;
	GUILayout* guiLayout;	
	QFileDialog qFileDialog;
};
