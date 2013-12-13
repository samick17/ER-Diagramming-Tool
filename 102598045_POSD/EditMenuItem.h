#pragma once

#include <QMenu>
#include "QActionMap.h"

class EditMenuItem : public QMenu{
public:
    EditMenuItem(QActionMap* actionMap,QWidget* parent);
    ~EditMenuItem();
};