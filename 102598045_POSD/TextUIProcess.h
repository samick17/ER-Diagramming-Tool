#pragma once

#include <QThread>
#include "TextUI.h"

#define SLEEP_TIME        0.5

class TextUIProcess : public QThread{
public:
    TextUIProcess(TextUI* textUI);
    ~TextUIProcess();
private:
    void run();
    TextUI* textUI;
};