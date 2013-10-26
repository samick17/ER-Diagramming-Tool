#include "GUILayout.h"
#include <QtGui/QApplication.h>
#include "ApplicationSetting.h"

GUILayout::GUILayout(){
}

GUILayout::~GUILayout(){
}

void GUILayout::setupUI(QMainWindow *mainWindow){
	setTitle(mainWindow);
	mainWindow->resize(600, 400);
    QMetaObject::connectSlotsByName(mainWindow);
}

void GUILayout::setTitle(QMainWindow *mainWindow){
	QString title = QString(ApplicationSetting::Title.c_str());
	mainWindow->setWindowTitle(title);
}