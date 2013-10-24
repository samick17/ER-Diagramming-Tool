#pragma once

#include <Qt\qthread.h>
#include <string>

using namespace std;

class MyThread : public QThread{
public:
	MyThread();
	~MyThread();

protected:
	void run();
private:
};