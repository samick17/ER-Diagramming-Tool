#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenuBar>
#include <QToolBar>
#include "FileMenuItem.h"
#include "QActionMap.h"
#include "IObserver.h"

class GraphicalPresentation;
class SelectedFrameWidget;

using namespace Qt;

class GraphicalUI : public QMainWindow,IObserver{
    Q_OBJECT
public slots:
    void openFile();
    void close();
public:
    GraphicalUI(GraphicalPresentation* graphicalPresentation);
    ~GraphicalUI();

    void displayDiagram();

    GraphicalPresentation* getGraphicalPresentation();
    void notify();
protected:
    void closeEvent(QCloseEvent* closeEvent);
    void keyPressEvent(QKeyEvent* keyEvent);
    void keyReleaseEvent(QKeyEvent* keyEvent);
private:
    GraphicalPresentation* graphicalPresentation;
    FileMenuItem* fileMenuItem;
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QActionMap* actionMap;

    void setTitle(string title);
    void initialGraphicView();
    void initialAllAction();
    void initialMenuBar();
    void initialToolBar();
    void refresh();
};