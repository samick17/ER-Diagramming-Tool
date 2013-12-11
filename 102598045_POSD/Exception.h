#pragma once

#include <string>
#include <exception.h>

using namespace std;

class Exception : public exception{
public:
    Exception();
    Exception(string message);
    virtual ~Exception();

    const char* what() const;
protected:
    string message;
};