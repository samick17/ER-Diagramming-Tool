#pragma once

#include <QToolButton>
#include "QActionMap.h"

class SetPointerWidget : public QToolButton{
public:
    SetPointerWidget(QActionMap* actionMap,QWidget* parent = 0);
	~SetPointerWidget();
};