#pragma once

#include <string>
#include "Rect.h"
#include "StringSymbol.h"

using namespace std;

struct ComponentData{
public:
    ComponentData(string type,string id,string name = StringSymbol::Empty);
    virtual ~ComponentData();

    string getID();
    void setID(string id);
    string getName();
    void setName(string name);
    string getType();
    string getClassName();
    bool getIsUnderLine();
    void setIsUnderLine(bool isUnderLine);
    Point getPosition();
    Size getSize();
    Rect getRect();
    void setPosition(Point position);
    void setCenterPosition(Point position);
    void setSize(Size size);

    bool operator==(const ComponentData& componentDataToCompare) const;
private:
    string id;
    string name;
    string type;
    string className;
    bool isUnderLine;
    Rect rect;
};