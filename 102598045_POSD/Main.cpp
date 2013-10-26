#include "TextUIProcess.h"
#include "GraphicalUI.h"
#include "ERModel.h"
#include "CommandManager.h"
#include "TextUI.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[]){
	QApplication  app(argc, argv);
	
	ERModel erModel;	
	Presentation presentation(&erModel);
	CommandManager commandManager(&presentation);
	presentation.setCommandManager(&commandManager);
	TextUI textUI(&presentation);

	TextUIProcess textUIProcess(&textUI);
	textUIProcess.start();

	GraphicalUI gui(&presentation);
	gui.show();	
	return app.exec();
}