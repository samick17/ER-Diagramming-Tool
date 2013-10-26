#pragma once

#include <QtGui/QMainWindow>
#include "GUILayout.h"

using namespace Qt;

class GraphicalUI : public QMainWindow{
	Q_OBJECT
public:
	GraphicalUI(QWidget *parent = 0, WFlags flags = 0);
	~GraphicalUI();
private:
	GUILayout guiLayout;
};
