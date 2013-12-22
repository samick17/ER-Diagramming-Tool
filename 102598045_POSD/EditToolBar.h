#pragma once

#include <QToolBar>
#include <QMutex>
#include "QActionMap.h"
#include "IObserver.h"

class GraphicalUI;
class GraphicalPresentation;

class EditToolBar : public QToolBar,public IObserver{
    Q_OBJECT
signals:
    void onNotifyEvent();
public:
    EditToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~EditToolBar();

    void notify(Subject* subject);
private:
    void refresh();
    GraphicalPresentation* graphicalPresentation;
    QMutex mutex;
private slots:
    void executeNotify();
};