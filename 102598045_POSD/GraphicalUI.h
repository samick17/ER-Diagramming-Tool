#pragma once

#include <QtGui/QMainWindow>
#include "GUILayout.h"
#include "Presentation.h"

using namespace Qt;

class GraphicalUI : public QMainWindow{
	Q_OBJECT
public:
	GraphicalUI(Presentation* presentation,QWidget *parent = 0, WFlags flags = 0);
	~GraphicalUI();
private:
	Presentation* presentation;
	GUILayout guiLayout;	
};
