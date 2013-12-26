#pragma once

#include "FileProcess.h"
#include "HashMap.h"

class Component;

class OutputFileProcess : public FileProcess{
public:
    OutputFileProcess(string filePath,HashMap<string,Component*> componentMap);
    ~OutputFileProcess();

    void saveFile();
private:
    void saveERDFile();
    void saveXmlFile();
    typedef void (OutputFileProcess::*SaveFileFunction)();
    HashMap<string,SaveFileFunction> saveFileFunctionMap;
    HashMap<string,Component*> componentMap;
};