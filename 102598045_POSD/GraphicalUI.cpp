#include "GraphicalUI.h"

GraphicalUI::GraphicalUI(Presentation* presentation,QWidget *parent, WFlags flags): presentation(presentation),QMainWindow(parent, flags){
	guiLayout.setupUI(this);
}

GraphicalUI::~GraphicalUI(){
}