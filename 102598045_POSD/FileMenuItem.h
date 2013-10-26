#pragma once

#include <QMenu>

class GraphicalUI;

class FileMenuItem : public QMenu{
public:
	FileMenuItem(GraphicalUI* graphicalUI);
	~FileMenuItem();
private:
	QAction* openFileAction;
	QAction* exitAction;
};