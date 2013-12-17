#pragma once

#include <QToolBar>
#include "QActionMap.h"
#include "ToolBarWidget.h"
#include "HashMap.h"
#include "IObserver.h"

class StateSubject;
class GraphicalUI;

class AddDrawableToolBar : public QToolBar,public IObserver{
public:
    AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~AddDrawableToolBar();

    void notify(Subject* subject);
private:
    void selectToolButton(int stateID);
    ToolBarWidget* currentFocusedWidget;
    StateSubject* stateSubject;
    HashMap<int,ToolBarWidget*> toolBarWidgetMap;
};