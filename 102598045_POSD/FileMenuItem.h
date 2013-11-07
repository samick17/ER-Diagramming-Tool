#pragma once

#include <QMenu>
#include "QActionMap.h"

class FileMenuItem : public QMenu{
public:
    FileMenuItem(QActionMap* actionMap);
    ~FileMenuItem();
};