#pragma once

#include <QTableWidget>
#include "IObserver.h"

class GraphicalPresentation;

using namespace std;

class GUIComponentTableView : public QTableWidget,public IObserver{
    Q_OBJECT
public:
    GUIComponentTableView(GraphicalPresentation* graphicalPresentation);
    ~GUIComponentTableView();

    void notify(Subject* subject);
private:
    static const int TableSize;
    static const string TableColumnTypeName;
    static const string TableColumnTextName;
    GraphicalPresentation* graphicalPresentation;
private slots:
    void onItemChanged(QTableWidgetItem* tableWidgetItem);
};