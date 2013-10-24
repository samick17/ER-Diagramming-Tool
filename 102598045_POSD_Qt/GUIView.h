#pragma once

#include <QtGui/QMainWindow>
#include "ui_qtapptest.h"

using namespace Qt;
using namespace Ui;

class GUIView : public QMainWindow{
	Q_OBJECT
public:
	GUIView(QWidget *parent = 0, WFlags flags = 0);
	~GUIView();
private:
	QTAppTestClass ui;
};
