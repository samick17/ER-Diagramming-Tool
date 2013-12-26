#pragma once

#include "Document.h"
#include "HashMap.h"

class Component;

class ERDDocument : public Document{
public:
    ERDDocument(string fileName,HashMap<string,Component*> componentMap);
protected:
    void doSaveFile();
private:
    HashMap<string,Component*> componentMap;
};