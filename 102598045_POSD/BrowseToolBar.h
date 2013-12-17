#pragma once

#include <QToolBar>
#include "QActionMap.h"
#include "IObserver.h"

class GraphicalUI;
class GraphicalPresentation;
class ToolBarWidget;

class BrowseToolBar : public QToolBar,public IObserver{
public:
    BrowseToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~BrowseToolBar();

    void notify(Subject* subject);
private:
    ToolBarWidget* browseDBTableWidget;
    GraphicalPresentation* graphicalPresentation;
};