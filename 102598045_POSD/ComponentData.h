#pragma once

#include <string>
#include "Rect.h"

using namespace std;

struct ComponentData{
public:
    ComponentData(string id,string name,string type);
    virtual ~ComponentData();

    string getID();
    void setID(string id);
    string getName();
    void setName(string name);
    string getType();
    bool getIsUnderLine();
    void setIsUnderLine(bool isUnderLine);
    Rect getRect();
    void setPosition(Point position);
    void setCenterPosition(Point position);
    void setSize(Size size);

    bool operator==(const ComponentData& componentDataToCompare) const;
private:
    string id;
    string name;
    string type;
    bool isUnderLine;
    Rect rect;
};