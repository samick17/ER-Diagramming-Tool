#pragma once

#include <QString>
#include <QKeySequence>
#include <string>

using namespace std;

struct QActionData{
public:
    QActionData(string actionText,string iconPath,string keySequence);
    ~QActionData();

    string getActionText();
    string getIconPath();
    QKeySequence getKeySequence();
private:
    string actionText;
    string iconPath;
    QKeySequence keySequence;
};