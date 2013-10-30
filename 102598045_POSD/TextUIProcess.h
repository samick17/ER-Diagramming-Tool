#pragma once

#include <QThread>
#include <QMutex>
#include <string>
#include "TextUI.h"

using namespace std;

class TextUIProcess : public QThread{
public:
    TextUIProcess(TextUI* textUI);
    ~TextUIProcess();

    void requestStop();
private:
    void run();
    QMutex mutex;
    bool stopRequested;
    TextUI* textUI;
};