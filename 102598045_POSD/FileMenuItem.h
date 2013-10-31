#pragma once

#include <QMenu>
#include "QActionMap.h"

class GraphicalUI;

class FileMenuItem : public QMenu{
public:
    FileMenuItem(QActionMap* actionMap);
    ~FileMenuItem();
};