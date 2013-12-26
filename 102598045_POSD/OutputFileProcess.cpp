#include "OutputFileProcess.h"
#include "ApplicationSetting.h"
#include "StringUtil.h"
#include "CharSymbol.h"
#include "ERDDocument.h"
#include "XmlDocument.h"

OutputFileProcess::OutputFileProcess(string filePath,HashMap<string,Component*> componentMap) : FileProcess(filePath),componentMap(componentMap){
    this->saveFileFunctionMap.put(ApplicationSetting::ERDFileExtension,&OutputFileProcess::saveERDFile);
    this->saveFileFunctionMap.put(ApplicationSetting::XmlFileExtension,&OutputFileProcess::saveXmlFile);
}

OutputFileProcess::~OutputFileProcess(){
}

void OutputFileProcess::saveFile(){
    //save file according to file extension
    SaveFileFunction saveFileFunction = this->saveFileFunctionMap.get(this->getFileExtension());
    (this->*saveFileFunction)();
}
//save erd format file(with pos file)
void OutputFileProcess::saveERDFile(){
    ERDDocument document(this->getFileName(),this->componentMap);
    document.saveFile();
}
//save xml format file
void OutputFileProcess::saveXmlFile(){
    XmlDocument document(this->getFileName(),this->componentMap);
    document.saveFile();
}