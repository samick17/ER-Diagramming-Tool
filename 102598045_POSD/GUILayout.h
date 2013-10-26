#pragma once

#include <QtGui/QMainWindow>
#include <string>

using namespace std;

class GUILayout{
public:
	GUILayout();
	~GUILayout();
    void setupUI(QMainWindow *mainWindow);
private:
	void setTitle(QMainWindow *mainWindow);
};