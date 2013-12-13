#pragma once

#include <QToolBar>
#include "QActionMap.h"

class GraphicalUI;

class FileToolBar : public QToolBar{
public:
    FileToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~FileToolBar();
};