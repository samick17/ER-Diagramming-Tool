#pragma once

#include <string>

using namespace std;

class Exception{
public:
	Exception();
	Exception(string message);
	virtual ~Exception();

	string getMessage();
protected:
	string message;
};