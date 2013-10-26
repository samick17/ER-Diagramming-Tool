#pragma once

#include <QMenuBar>

class GraphicalUI;

using namespace std;

class GUILayout{
public:
	GUILayout(GraphicalUI* graphicalUI);
	~GUILayout();
    void initialGUILayout();
private:
	GraphicalUI* graphicalUI;
	QMenuBar menuBar;
	void setTitle();
	void initialMenuBar();
};