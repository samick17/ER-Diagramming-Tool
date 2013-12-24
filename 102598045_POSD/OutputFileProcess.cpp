#include "OutputFileProcess.h"
#include "ApplicationSetting.h"
#include "StringUtil.h"
#include "CharSymbol.h"
#include "ERDDocument.h"
#include "XmlDocument.h"

OutputFileProcess::OutputFileProcess(string filePath,HashMap<string,Component*> componentMap) : componentMap(componentMap){
    this->saveFileFunctionMap.put(ApplicationSetting::ERDFileExtension,&OutputFileProcess::saveERDFile);
    this->saveFileFunctionMap.put(ApplicationSetting::XmlFileExtension,&OutputFileProcess::saveXmlFile);
    this->extractFileInfo(filePath);
}

OutputFileProcess::~OutputFileProcess(){
}

void OutputFileProcess::saveFile(){
    //save file according to file extension
    SaveFileFunction saveFileFunction = this->saveFileFunctionMap.get(this->fileExtension);
    (this->*saveFileFunction)();
}
//save erd format file(with pos file)
void OutputFileProcess::saveERDFile(){
    ERDDocument document(this->fileName,this->componentMap);
    document.saveFile();
}
//save xml format file
void OutputFileProcess::saveXmlFile(){
    XmlDocument document(this->fileName,this->componentMap);
    document.saveFile();
}
//get File Extension, if doesnot contains File Extension, throw exception
void OutputFileProcess::extractFileInfo(string filePath){
    unsigned int lastIndex = StringUtil::lastIndexOf(filePath,CharSymbol::Dot);
    if(lastIndex == -1)
        throw Exception("Please enter correct format!");
    this->fileName = filePath.substr(0,lastIndex);
    this->fileExtension = filePath.substr(lastIndex);
}