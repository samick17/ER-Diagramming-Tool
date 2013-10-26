#pragma once

#include <Qt\qthread.h>
#include <string>

using namespace std;

class TextUIProcess : public QThread{
public:
	TextUIProcess();
	~TextUIProcess();

protected:
	void run();
private:
};