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

    Presentation presentation(&erModel);

    TextPresentation textPresentation(&presentation);
    TextUI textUI(&textPresentation);
    TextUIProcess textUIProcess(&textUI);
    textUIProcess.start();

    GraphicalPresentation graphicalPresentation(&presentation);
    GraphicalUI graphicalUI(&graphicalPresentation);

    graphicalUI.show();
    return app.exec();
}