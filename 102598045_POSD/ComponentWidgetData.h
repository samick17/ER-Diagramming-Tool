#pragma once

#include <string>

using namespace std;

struct ComponentWidgetData{
public:
    ComponentWidgetData(string text,int positionX,int positionY,bool isUnderLined = false);
    ~ComponentWidgetData();

    string getText();
	void setText(string text);
    int getPositionX();
	void setPositionX(int positionX);
    int getPositionY();
	void setPositionY(int positionY);
    bool getIsUnderLined();
	void setIsUnderLined(bool isUnderLined);
private:
    string text;
    int positionX;
    int positionY;
    bool isUnderLined;
};