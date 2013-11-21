#pragma once

#include <string>
#include "StringSymbol.h"

using namespace std;

struct QActionData{
public:
    QActionData(unsigned int actionIndex);
    ~QActionData();

    unsigned int getActionIndex();
    string getActionText();
    string getIconPath();
    string getKeySequence();
private:
    unsigned int actionIndex;
    string actionText;
    string iconPath;
    string keySequence;
};