#pragma once

#include <QTableWidget>
#include <QLabel>
#include <string>
#include "IObserver.h"

class GraphicalPresentation;

using namespace std;

class GUITableView : public QTableWidget,public IObserver{
    Q_OBJECT;
public:
    GUITableView(GraphicalPresentation* graphicalPresentation);
    ~GUITableView();

    void notify(ISubject* subject);
private:
    GraphicalPresentation* graphicalPresentation;
    static const string TableTitle;
    static const int TableSize;
    static const string TableColumnTypeName;
    static const string TableColumnTextName;
private slots:
    void onItemChanged();
};