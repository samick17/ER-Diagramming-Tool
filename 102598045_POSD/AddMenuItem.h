#pragma once

#include <QMenu>
#include "QActionMap.h"

class AddMenuItem : public QMenu{
public:
    AddMenuItem(QActionMap* actionMap,QWidget* parent);
    ~AddMenuItem();
};