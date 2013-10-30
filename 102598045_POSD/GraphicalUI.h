#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenuBar>
#include <QToolBar>
#include "FileMenuItem.h"

class GraphicalPresentation;

using namespace Qt;

class GraphicalUI : public QMainWindow{
    Q_OBJECT
public slots:
    void openFile();
    void close();
public:
    GraphicalUI(GraphicalPresentation* graphicalPresentation);
    ~GraphicalUI();

    void displayComponents();

    GraphicalPresentation* getGraphicalPresentation();
protected:
	void closeEvent ( QCloseEvent * event );
private:
    GraphicalPresentation* graphicalPresentation;
    FileMenuItem* fileMenuItem;
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QGraphicsView* view;
    QGraphicsScene* scene;

    void setTitle();
    void initialMenuBar();
    void initialToolBar();
};
