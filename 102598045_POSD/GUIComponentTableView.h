#pragma once

#include <QTableWidget>
#include <QMutex>
#include "IObserver.h"

class GraphicalPresentation;

using namespace std;

class GUIComponentTableView : public QTableWidget,public IObserver{
    Q_OBJECT
signals:
    void onNotifyEvent();
public:
    GUIComponentTableView(GraphicalPresentation* graphicalPresentation);
    ~GUIComponentTableView();

    void notify(Subject* subject);
private:
    void refresh();
    static const int TableSize;
    static const string TableColumnTypeName;
    static const string TableColumnTextName;
    GraphicalPresentation* graphicalPresentation;
    QMutex mutex;
private slots:
    void onItemChanged(QTableWidgetItem* tableWidgetItem);
    void executeNotify();
};