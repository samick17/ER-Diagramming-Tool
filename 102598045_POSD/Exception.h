#pragma once

#include <exception>
#include <string>

using namespace std;

class Exception : public exception{
public:
    Exception();
    Exception(string message);
    virtual ~Exception();

    const char* what();
protected:
    string message;
};