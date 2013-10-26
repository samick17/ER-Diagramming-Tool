#include "GraphicalUI.h"

GraphicalUI::GraphicalUI(QWidget *parent, WFlags flags): QMainWindow(parent, flags){
	guiLayout.setupUI(this);
}

GraphicalUI::~GraphicalUI(){
}