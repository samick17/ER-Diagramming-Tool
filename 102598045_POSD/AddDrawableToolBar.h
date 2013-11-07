#pragma once

#include <QToolBar>
#include "QActionMap.h"

class AddDrawableToolBar : public QToolBar{
public:
    AddDrawableToolBar(QActionMap* actionMap,QWidget* parent = 0);
    ~AddDrawableToolBar();
};