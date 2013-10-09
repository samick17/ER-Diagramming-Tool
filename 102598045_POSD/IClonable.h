#pragma once

class IClonable{
public:
    virtual ~IClonable();
    virtual IClonable* clone() const = 0;
};