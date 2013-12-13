#pragma once

#include <QMenu>
#include "QActionMap.h"

class HelpMenuItem : public QMenu{
public:
    HelpMenuItem(QActionMap* actionMap,QWidget* parent);
    ~HelpMenuItem();
};