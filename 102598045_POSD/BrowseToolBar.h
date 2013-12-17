#pragma once

#include <QToolBar>
#include "QActionMap.h"
#include "ToolBarWidget.h"
#include "IObserver.h"

class GraphicalUI;
class GraphicalPresentation;

class BrowseToolBar : public QToolBar,public IObserver{
public:
    BrowseToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~BrowseToolBar();

    void notify(Subject* subject);
private:
    ToolBarWidget* browseDBTableWidget;
    GraphicalPresentation* graphicalPresentation;
};