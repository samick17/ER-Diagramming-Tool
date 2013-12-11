#include "Exception.h"

Exception::Exception(){
}

Exception::Exception(string message) : message(message){
}

Exception::~Exception(){
}

const char* Exception::what() const{
    return this->message.c_str();
}