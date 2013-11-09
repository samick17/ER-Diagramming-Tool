#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenuBar>
#include <QToolBar>
#include "GUIScene.h"
#include "FileMenuItem.h"
#include "FileToolBar.h"
#include "AddDrawableToolBar.h"
#include "QActionMap.h"
#include "ISynchronizer.h"

class GraphicalPresentation;
class SelectedFrameWidget;

using namespace Qt;

class GraphicalUI : public QMainWindow,ISynchronizer{
    Q_OBJECT
signals:
    void syncEvent(int syncEventType);
public:
    GraphicalUI(GraphicalPresentation* graphicalPresentation);
    ~GraphicalUI();

    GraphicalPresentation* getGraphicalPresentation();
    void sync(int syncEventType);
    void setTitle(string title);

    void mousePress(QPointF position);
    void mouseMove(QPointF position);
    void mouseRelease(QPointF position);
protected:
    void closeEvent(QCloseEvent* closeEvent);
    void keyPressEvent(QKeyEvent* keyEvent);
    void keyReleaseEvent(QKeyEvent* keyEvent);
private:
    GraphicalPresentation* graphicalPresentation;
    FileMenuItem* fileMenuItem;
    FileToolBar* fileToolBar;
    AddDrawableToolBar* addDrawableToolBar;
    QMenuBar* menuBar;
    QGraphicsView* view;
    GUIScene* scene;
    QActionMap* actionMap;
    typedef void (GraphicalUI::*ViewSyncFunction)();
    HashMap<int,ViewSyncFunction> syncMap;

    void initialGraphicView();
    void initialAllAction();
    void initialMenuBar();
    void initialToolBar();
    void initialSyncMap();
    void refresh();
    void displayDiagram();
private slots:
    void openFile();
    void close();
    void switchState(int stateID);
    void executeSync(int syncEventType);
};