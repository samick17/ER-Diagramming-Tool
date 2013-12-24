#pragma once

#include "Document.h"
#include "HashMap.h"

class Component;

class XmlDocument : public Document{
public:
    XmlDocument(string fileName);
    XmlDocument(string fileName,HashMap<string,Component*> componentMap);
protected:
    void doSaveFile();
private:
    HashMap<string,Component*> componentMap;
};