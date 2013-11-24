#pragma once

#include <QTableWidget>
#include <QLabel>
#include <string>
#include "IObserver.h"

class GraphicalPresentation;

using namespace std;

class GUITableView : public QWidget,public IObserver{
public:
    GUITableView(GraphicalPresentation* graphicalPresentation);
    ~GUITableView();

    void notify(ISubject* subject);
private:
    QLabel* titleLabel;
    QTableWidget* tableWidget;
    GraphicalPresentation* graphicalPresentation;
    static const string TableTitle;
    static const int TableSize;
    static const string TableColumnTypeName;
    static const string TableColumnTextName;
};