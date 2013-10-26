#include "TextUIProcess.h"
#include "GraphicalUI.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[]){
	TextUIProcess textUIProcess;

	textUIProcess.start();

	QApplication  app(argc, argv);
	
	GraphicalUI gui;
	gui.show();	
	return app.exec();	
}