#include "GUIView.h"

GUIView::GUIView(QWidget *parent, WFlags flags): QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

GUIView::~GUIView()
{
	delete ui.statusBar;
	delete ui.menuBar;
	delete ui.mainToolBar;
	delete ui.centralWidget;
}