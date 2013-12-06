#pragma once

#include <string>
#include "StringSymbol.h"
#include <gtest/gtest_prod.h>

using namespace std;

struct QActionData{
    friend class QActionDataTest;
    FRIEND_TEST(QActionDataTest,testInitialToolTip);
public:
    QActionData(unsigned int actionIndex);
    ~QActionData();

    unsigned int getActionIndex();
    string getActionText();
    string getIconPath();
    string getKeySequence();
    string getToolTip();
private:
    string initialToolTip(string actionText,string keySequence);

    unsigned int actionIndex;
    string actionText;
    string iconPath;
    string keySequence;
    string toolTip;
};