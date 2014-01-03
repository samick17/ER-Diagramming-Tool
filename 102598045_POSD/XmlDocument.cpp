#include "XmlDocument.h"
#include "ReorderComponentsUtil.h"
#include "SaveXmlComponentVisitor.h"
#include "ApplicationSetting.h"

XmlDocument::XmlDocument(string fileName,HashMap<string,Component*> componentMap) : Document(fileName,ApplicationSetting::XmlFileExtension),componentMap(componentMap){
}

void XmlDocument::doSaveFile(){
    HashMap<string,string> orderedIDsMap = ReorderComponentsUtil::getReorderedComponentIDMap(this->componentMap);
    SaveXmlComponentVisitor saveXmlComponentVisitor = SaveXmlComponentVisitor(orderedIDsMap);
    //accept all
    for each(Component* component in this->componentMap)
        component->accept(&saveXmlComponentVisitor);
    //save erd file
    for each(string info in saveXmlComponentVisitor.getResult())
        this->writeLine(info);
}