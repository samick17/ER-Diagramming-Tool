#pragma once

#include <string>
#include "StringSymbol.h"

using namespace std;

struct QActionData{
public:
    QActionData(string actionText,string iconPath,string keySequence = StringSymbol::Empty);
    ~QActionData();

    string getActionText();
    string getIconPath();
    string getKeySequence();
private:
    string actionText;
    string iconPath;
    string keySequence;
};