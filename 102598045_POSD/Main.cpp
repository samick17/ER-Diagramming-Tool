#include "TextUIProcess.h"
#include "GraphicalUI.h"
#include "TextPresentation.h"
#include "GraphicalPresentation.h"
#include "ERModel.h"
#include "CommandManager.h"
#include "TextUI.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication  app(argc, argv);
    
    ERModel erModel;
    TextPresentation textPresentation(&erModel);
    TextUI textUI(&textPresentation);
    textPresentation.setTextUI(&textUI);
	
    TextUIProcess textUIProcess(&textUI);
    textUIProcess.start();

	GraphicalPresentation graphicalPresentation(&erModel);
    GraphicalUI gui(&graphicalPresentation);
    gui.show();
    
    return app.exec();
}