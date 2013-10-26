#include "GUILayout.h"
#include "GraphicalUI.h"
#include "ApplicationSetting.h"
#include "FileMenuItem.h"

GUILayout::GUILayout(GraphicalUI* graphicalUI) : graphicalUI(graphicalUI){
	setTitle();	
	this->initialMenuBar();
	this->graphicalUI->resize(ApplicationSetting::DefaultWidth,ApplicationSetting::DefaultHeight);
    QMetaObject::connectSlotsByName(graphicalUI);
}

GUILayout::~GUILayout(){
}

void GUILayout::setTitle(){
	QString title = QString(ApplicationSetting::Title.c_str());
	this->graphicalUI->setWindowTitle(title);
}

void GUILayout::initialMenuBar(){
	this->menuBar.addMenu(new FileMenuItem(this->graphicalUI));
	this->graphicalUI->setMenuBar(&this->menuBar);	
}