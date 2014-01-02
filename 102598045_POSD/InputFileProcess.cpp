#include "InputFileProcess.h"
#include "ApplicationSetting.h"
#include "InputFileParser.h"

InputFileProcess::InputFileProcess(string filePath,ERModel* erModel) : FileProcess(filePath),erModel(erModel){
    this->openFileFunctionMap.put(ApplicationSetting::ERDFileExtension,&InputFileProcess::openERDFile);
}

InputFileProcess::~InputFileProcess(){
}

void InputFileProcess::openFile(){
    //save file according to file extension
    OpenFileFunction openFileFunction = this->openFileFunctionMap.get(this->getFileExtension());
    (this->*openFileFunction)();
}

void InputFileProcess::openERDFile(){
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(this->getFileName(),this->getFileExtension(),this->erModel);
}