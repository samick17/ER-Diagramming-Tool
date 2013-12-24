#pragma once

#include <string>
#include "HashMap.h"

class Component;

using namespace std;

class OutputFileProcess{
public:
    OutputFileProcess(string filePath,HashMap<string,Component*> componentMap);
    ~OutputFileProcess();

    void saveFile();
private:
    void saveERDFile();
    void saveXmlFile();
    void extractFileInfo(string filePath);
    typedef void (OutputFileProcess::*SaveFileFunction)();
    HashMap<string,SaveFileFunction> saveFileFunctionMap;
    string fileName,fileExtension;
    HashMap<string,Component*> componentMap;
};