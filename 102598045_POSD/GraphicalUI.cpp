#include "GraphicalUI.h"
#include "Presentation.h"

GraphicalUI::GraphicalUI(Presentation* presentation,QWidget *parent, WFlags flags): presentation(presentation),QMainWindow(parent, flags){
	this->guiLayout = new GUILayout(this);
}

GraphicalUI::~GraphicalUI(){
	delete this->guiLayout;
}

Presentation* GraphicalUI::getPresentation(){
	return this->presentation;
}

void GraphicalUI::openFile(){
	QString fileName = qFileDialog.getOpenFileName(this, tr("Open File"),"",tr("Files (*.erd)"));
}