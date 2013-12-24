#include "OutputFileProcess.h"
#include "ReorderComponentsUtil.h"
#include "SaveComponentVisitor.h"
#include "SaveXmlComponentVisitor.h"
#include "ApplicationSetting.h"
#include "StringUtil.h"
#include "CharSymbol.h"

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
    HashMap<string,string> orderedIDsMap = ReorderComponentsUtil::getReorderedComponentIDMap(this->componentMap);
    SaveComponentVisitor saveComponentVisitor = SaveComponentVisitor(orderedIDsMap);
    //accept all
    for each(Component* component in this->componentMap)
        component->accept(&saveComponentVisitor);
    //save erd file
    Document erdDoc(this->fileName+ApplicationSetting::ERDFileExtension);
    for each(string info in saveComponentVisitor.getResult())
        erdDoc.writeLine(info);
    erdDoc.saveFile();
    //save pos file
    Document posDoc(this->fileName+ApplicationSetting::ERDPositionFileExtension);
    for each(string position in saveComponentVisitor.getPositionInfoVector())
        posDoc.writeLine(position);
    posDoc.saveFile();
}
//save xml format file
void OutputFileProcess::saveXmlFile(){
    HashMap<string,string> orderedIDsMap = ReorderComponentsUtil::getReorderedComponentIDMap(this->componentMap);
    SaveXmlComponentVisitor saveXmlComponentVisitor = SaveXmlComponentVisitor(orderedIDsMap);
    //accept all
    for each(Component* component in this->componentMap)
        component->accept(&saveXmlComponentVisitor);
    //save erd file
    Document xmlDoc(this->fileName+ApplicationSetting::XmlFileExtension);
    xmlDoc.writeLine("<?xml version=\"1.0\"?>");
    xmlDoc.writeLine("<ERDiagram>");
    for each(string info in saveXmlComponentVisitor.getResult())
        xmlDoc.writeLine(info);
    xmlDoc.writeLine("</ERDiagram>");
    xmlDoc.saveFile();
}
//get File Extension, if doesnot contains File Extension, throw exception
void OutputFileProcess::extractFileInfo(string filePath){
    unsigned int lastIndex = StringUtil::lastIndexOf(filePath,CharSymbol::Dot);
    if(lastIndex == -1)
        throw Exception("Please enter correct format!");
    this->fileName = filePath.substr(0,lastIndex);
    this->fileExtension = filePath.substr(lastIndex);
}