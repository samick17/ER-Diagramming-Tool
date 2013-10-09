#include "Exception.h"

Exception::Exception(){
}

Exception::Exception(string message) : message(message)
{
}

Exception::~Exception(){
}

string Exception::getMessage(){
	return this->message;
}