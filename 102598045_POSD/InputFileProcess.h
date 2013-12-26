#pragma once

#include "FileProcess.h"
#include "HashMap.h"

class ERModel;
class Component;

class InputFileProcess : public FileProcess{
public:
    InputFileProcess(string filePath,ERModel* erModel);
    ~InputFileProcess();

    void openFile();
private:
    void openERDFile();
    typedef void (InputFileProcess::*OpenFileFunction)();
    HashMap<string,OpenFileFunction> openFileFunctionMap;
    ERModel* erModel;
};