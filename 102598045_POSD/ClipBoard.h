#pragma once

#include "HashMap.h"

class Component;

class ClipBoard{
public:
    ClipBoard();
    ~ClipBoard();

    void setData(HashMap<string,Component*> componentMap);
    HashMap<string,Component*> getData();
private:
    HashMap<string,Component*> componentMap;
};