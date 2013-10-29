#pragma once

#include <QThread>
#include <string>
#include "TextUI.h"

using namespace std;

class TextUIProcess : public QThread{
public:
    TextUIProcess(TextUI* textUI);
    ~TextUIProcess();
protected:
    void run();
private:
    TextUI* textUI;
};