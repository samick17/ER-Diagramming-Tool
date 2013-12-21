#pragma once

#include <QGraphicsScene>
#include <QMutex>
#include "IObserver.h"

class GraphicalUI;
class GraphicalPresentation;
class Table;

class GUITableScene : public QGraphicsScene,public IObserver{
    Q_OBJECT
signals:
    void onNotifyEvent();
public:
    GUITableScene(GraphicalUI* graphicalUI);
    ~GUITableScene();

    void notify(Subject* subject);
private:
    void refresh();
    void addWidget(Table* table,unsigned int index);
    GraphicalUI* graphicalUI;
    GraphicalPresentation* graphicalPresentation;
    QMutex mutex;
private slots:
    void executeNotify();
};