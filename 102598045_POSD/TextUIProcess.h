#pragma once

#include <QThread>
#include "TextUI.h"

class TextUIProcess : public QThread{
public:
    TextUIProcess(TextUI* textUI);
    ~TextUIProcess();
private:
    void run();
    TextUI* textUI;
};