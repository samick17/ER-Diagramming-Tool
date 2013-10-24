/********************************************************************************
** Form generated from reading UI file 'qtapptest.ui'
**
** Created: Thu Oct 24 00:22:05 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

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

QT_BEGIN_NAMESPACE

class Ui_QTAppTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;


    void setupUi(QMainWindow *QTAppTestClass)
    {
        if (QTAppTestClass->objectName().isEmpty())
            QTAppTestClass->setObjectName(QString::fromUtf8("QTAppTestClass"));
        QTAppTestClass->resize(600, 400);
        menuBar = new QMenuBar(QTAppTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QTAppTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTAppTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTAppTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTAppTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTAppTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTAppTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTAppTestClass->setStatusBar(statusBar);

        retranslateUi(QTAppTestClass);

        QMetaObject::connectSlotsByName(QTAppTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTAppTestClass)
    {
        QTAppTestClass->setWindowTitle(QApplication::translate("QTAppTestClass", "QTAppTest", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QTAppTestClass: public Ui_QTAppTestClass {};
} // namespace Ui

QT_END_NAMESPACE