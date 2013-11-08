#pragma once

#include <QToolBar>
#include "QActionMap.h"

class FileToolBar : public QToolBar{
public:
    FileToolBar(QActionMap* actionMap,QWidget* parent = NULL);
    ~FileToolBar();
};