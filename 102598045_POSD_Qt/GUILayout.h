#pragma once

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

class GUILayout{
public:
    void setupUI(QMainWindow *mainWindow){
		mainWindow->resize(600, 400);
        retranslateUi(mainWindow);
        QMetaObject::connectSlotsByName(mainWindow);
    }

    void retranslateUi(QMainWindow *mainWindow){
        mainWindow->setWindowTitle(QApplication::translate("QTAppTestClass", "Title", 0, QApplication::UnicodeUTF8));
    }

};