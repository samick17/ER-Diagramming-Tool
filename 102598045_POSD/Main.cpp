#include "TextUIProcess.h"
#include <QApplication>
#include "GraphicalUI.h"
#include "TextPresentation.h"
#include "GraphicalPresentation.h"
#include "ERModel.h"
#include "TextUI.h"

int main(int argc,char *argv[]){
    QApplication  app(argc,argv);
    //new ERModel & Presentation
    ERModel erModel;
    Presentation presentation(&erModel);
    //new Text UI & TextUI Process(Thread) & TextUI's Presentation
    TextPresentation textPresentation(&presentation);
    TextUI textUI(&textPresentation);
    TextUIProcess textUIProcess(&textUI);
    textUIProcess.start();
    //new GUI & GUI's Presentation
    GraphicalPresentation graphicalPresentation(&presentation);
    GraphicalUI graphicalUI(&graphicalPresentation);

    graphicalUI.show();
    return app.exec();
}